SELECT name from people
JOIN directors on people.id = directors.person_id
JOIN ratings on movies.id = ratings.movie_id
JOIN movies on directors.movie_id = movies.id
WHERE ratings.rating >= 9.0;