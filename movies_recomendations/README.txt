# Disney+ Movie Recommendation System

This project is a content-based recommendation system created to recommend movies and series from the Disney+ catalog. It receives 3 movie titles as command-line arguments and creates a user preference profile based on genre vectorization. The system uses cosine similarity to find and recommend the top 3 most similar movies from the catalog.

## Instructions for Build and Use

### Building the Project:

1. Open the solution file `movies_recomendations.sln` in Visual Studio 2022 or later
2. Ensure the project is set to use C++17 or later standard (__Project Properties > C/C++ > Language > C++ Language Standard__)
3. Make sure `titles.csv` is in the same directory as the executable (or adjust the path in the code)
4. Build the solution using __Build > Build Solution__ (or press `Ctrl+Shift+B`)

### Running the Program:

1. The program requires exactly 3 movie titles as command-line arguments
2. To run from Visual Studio with arguments:
   - Right-click the project → __Properties__
   - Navigate to __Configuration Properties > Debugging__
   - Set __Command Arguments__ to: `"Movie 1" "Movie 2" "Movie 3"`
   - Press `F5` to run with debugging or `Ctrl+F5` to run without debugging

3. To run from command line:
   - Navigate to the directory containing the executable
   - Run the program with the command: `MovieRecommender.exe "Movie 1" "Movie 2" "Movie 3"`
   - Ensure to replace `MovieRecommender.exe` with the actual name of the built executable

4. The program will output:
- Console display of found movies and recommendations
- A text file `recommendations.txt` with detailed results

## Development Environment

To recreate the development environment, you need the following software and/or libraries with the specified versions:

* **Visual Studio 2022 or later** with C++ developmenttools
* **C++17 Standard** or higher
* **csv-parser library** by Vincent La (vincentlaucsb/csv-parser on GitHub)
- Located in `lib/csv.hpp` directory
- Requires `lib/external/` folder with `string_view.hpp` and `hedley.h`
* **Windows 10/11** (developed and tested on Windows)
* **titles.csv** - Disney+ catalog dataset with columns: id, title, type, description, release_year, age_certification, runtime, genres, production_countries, seasons, imdb_id, imdb_score, imdb_votes, tmdb_popularity, tmdb_score

## Algorithm Overview

The recommendation system uses:
* **Genre Tokenization**: Converts movie genres into binary vectors
* **User Profile Creation**: Aggregates genre vectors from the 3 input movies
* **Cosine Similarity**: Measures similarity between user profile and catalog movies
* **Ranking**: Sorts all movies by similarity score and returns top 3 recommendations

## Useful Websites to Learn More

I found these websites useful in developing this software:

* [csv-parser Library Documentation](https://github.com/vincentlaucsb/csv-parser) - CSV parsing library used in this project
* [Cosine Similarity Explained](https://en.wikipedia.org/wiki/Cosine_similarity) - Understanding the similarity metric
* [C++ Regex Documentation](https://en.cppreference.com/w/cpp/regex) - Used for parsing genre strings
* [Content-Based Filtering](https://developers.google.com/machine-learning/recommendation/content-based/basics) - Recommendation system fundamentals

## Future Work

The following items I plan to fix, improve, and/or add to this project in the future:

* [ ] Add more genre categories beyond the current 5 (action, comedy, drama, scifi, animation)
* [ ] Implement weighted genre preferences (some genres matter more than others)
* [ ] Add additional features for similarity calculation (year, IMDB score, runtime, etc.)

* [ ] Support fuzzy matching for movie titles (handle typos and partial matches better)
* [ ] Create a GUI interface instead of command-line only
* [ ] Add support for TV series-specific features (number of seasons, episode count)
* [ ] Implement collaborative filtering alongside content-based filtering
* [ ] Allow users to specify number of recommendations (not fixed at 3)
* [ ] Add option to exclude certain genres from recommendations
* [ ] Create visualizations of user preference profiles and similarity scores