SELECT DISTINCT(name.people) FROM stars
JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movie_id
WHERE movies.year = 2004
ORDER BY birth ASC;