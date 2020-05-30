import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id =:id", id=session["user_id"])
    stocks = db.execute("SELECT stock, shares, total, price FROM portfolio WHERE id=:id", id=session["user_id"])
    # Incase no stocks owned
    if not stocks:
        return render_template("index1.html", cash=usd(cash[0]['cash']))
    else:
        prices = db.execute("SELECT stock, shares, total, price FROM portfolio WHERE id=:id", id=session["user_id"])
        for price in prices:
            symbol = prices[0]['stock']
            price = lookup(symbol)['price']
            shares = prices[0]['shares']
            total = price*shares
            db.execute("UPDATE portfolio SET price=:price, total=:total WHERE id=:id AND stock=:symbol", price=price,
                      total = total, id=session["user_id"], symbol=symbol)

        sumnums = db.execute("SELECT SUM(total) AS \"sumnums\" FROM portfolio WHERE id=:id", id=session["user_id"])
        if sumnums:
            all_total = sumnums[0]['sumnums']+(cash[0]['cash'])
        else:
            all_total = cash[0]['cash']
        return render_template("index.html", cash=usd(cash[0]['cash']), all_total=usd(all_total), stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("stock"):
            return apology("Stock does not exist", 400)
        # return apology if user does not enter a number of shares or if that number is not a positive integer
        if not request.form.get("shares") or not request.form.get("shares").isdigit() or float(request.form.get("shares")) % 1!= 0 or int(request.form.get("shares")) <= 0:
            return apology("Invalid number!", 400)
        stocks = lookup(request.form.get("symbol"))
        if not stocks:
            return apology("Incorrect Stock!", 400)
        # retrieve the user's cash money from the database
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

    # calculate the totaal value of the stock
        value = stocks["price"] * int(request.form.get("shares"))

    # return apology if value of stock is more than user's cash
        if value > cash[0]['cash']:
            return apology("Not eough money", 400)

    # update transactions table with purchase
        transaction = db.execute("INSERT INTO transactions (id, worth, shares, symbol, purchase, price) VALUES(:id, :worth, :shares, :symbol, :purchase, :price)",
                                id=session["user_id"], worth=value, shares=int(request.form.get("shares")), symbol=request.form.get("symbol"), price=stocks["price"], purchase="purchase")

    # update portfolio table
        update = db.execute("SELECT shares FROM portfolio WHERE id=:id AND stock=:symbol",
                           id=session["user_id"], symbol=request.form.get("symbol"))
        if not update:
            db.execute("INSERT INTO portfolio (id, stock, shares, price, total) VALUES(:id, :symbol, :shares, :total, :price)",
                      id=session["user_id"], symbol=request.form.get("symbol"), shares=int(request.form.get("shares")), total=value, price=stocks['price'])
        else:
            new_shares = update[0]['shares']+int(request.form.get('shares'))
            new_total = new_shares*stocks['price']
            db.execute("UPDATE portfolio SET shares=:shares, total=:total, price=:price WHERE id=:id and stock=:symbol",
                      shares=new_shares, total=new_total, id=session["user_id"], symbol=request.form.get("symbol"), price=stocks['price'])

    # determine user's new cash and update it in the users table
        new_cash = cash[0]['cash'] - value
        update = db.execute("UPDATE users SET cash = :value WHERE id = :id", value=new_cash, id=session["user_id"])
        return render_template("bought.html", cash=usd(new_cash), price=usd(stocks['price']), total=usd(value), shares=request.form.get("shares"), symbol=request.form
        .get("symbol"))


    else:
        render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, time, purchase FROM transactions WHERE id=:id", id=session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        render_template("quote.html")
    else:
        if not request.form.get("symbol"):
            return apology("Incorrect Symbol", 400)
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Symbol not found!", 400)
        else:
            symbol = stock["symbol"]
            price = stock["price"]
            return render_template("quoted.html", symbol=symbol, price=usd(price))
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        # Check for correct input
        name = request.form.get("name")
        if not name:
            return render_template("apolgy.html", message="Incorrect Username")
        password = request.form.get("password")
        if not password:
            return render_template("apolgy.html", message= "Incorrect Password")
        if request.form.get("password") != request.form.get("confirmation"):
            return render_template("apology.html", message="Unmatched Passwords!")
        # Generate hash for password
        hash_p = generate_password_hash(request.form.get("password"))
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                           username=request.form.get("username"),hash=hash_p)
        # Incase of unsuccessful insertion
        if not result:
            return render_template("apology.html", message="Username already exists!")
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                         username = request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))

        # Check if the symbol exists
        if quote == None:
            return apology("invalid symbol", 400)

        # Check if shares was a positive integer
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be a positive integer", 400)

        # Check if # of shares requested was 0
        if shares <= 0:
            return apology("can't sell less than or 0 shares", 400)

        # Check if we have enough shares
        stock = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol",
                           user_id=session["user_id"], symbol=request.form.get("symbol"))

        if len(stock) != 1 or stock[0]["total_shares"] <= 0 or stock[0]["total_shares"] < shares:
            return apology("you can't sell less than 0 or more than you own", 400)

        # Query database for username
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # How much $$$ the user still has in her account
        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]

        # Calculate the price of requested shares
        total_price = price_per_share * shares

        # Book keeping (TODO: should be wrapped with a transaction)
        db.execute("UPDATE users SET cash = cash + :price WHERE id = :user_id", price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price_per_share) VALUES(:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol"),
                   shares=-shares,
                   price=price_per_share)

        flash("Sold!")

        return redirect("index.html")

    else:
        stocks = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])

        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
