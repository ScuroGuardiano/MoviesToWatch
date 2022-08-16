#pragma once

#include <string>
#include <vector>

namespace pure_models {
  enum class MovieType {
    Movie = 1,
    Anime,
    AnimeMovie,
    Series
  };

  class MovieToWatch {
    public:
      uint64_t id = 0;
      std::string name;
      MovieType type = MovieType::Movie;
      uint32_t priority = 0;
      std::vector<std::string> tags;     
  };
}
