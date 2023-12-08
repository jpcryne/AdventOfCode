library(tidyverse)
input_raw <- read_lines(here::here("2023/day_08/input.txt"))

dirs <- unlist(strsplit(input_raw[1], ""))
map_df <- data.frame(raw = input_raw[3:length(input_raw)]) |>
  tidyr::separate_wider_delim(delim = " = ", names = c("location", "tmp"), cols = raw) |>
  tidyr::separate_wider_delim(delim = ", ", names = c("L", "R"), cols = tmp) |>
  dplyr::mutate(dplyr::across(c(L, R), \(x) gsub("\\(|\\)", "", x)))

# * Part 1
start = "AAA"
end = ""
steps = 0
while (end != "ZZZ") {
  dir <- dirs[1 + (steps %% length(dirs))]
  end <- map_df |>
    dplyr::filter(location == !!start) |>
    dplyr::pull(dplyr::all_of(dir))
  steps <- steps + 1
  start <- end
}

print(steps)

# # * Part 2
starts <- map_df |>
  dplyr::filter(grepl("A$", location)) |>
  dplyr::pull(location)

find_steps <- function(start, map_df, dirs) {
  end <- ""
  steps <- 0
  while (!grepl("Z$", end)) {
    dir <- dirs[1 + (steps %% length(dirs))]
    end <- map_df |>
      dplyr::filter(location %in% !!start) |>
      dplyr::pull(dplyr::all_of(dir))
    steps <- steps + 1
    start <- end
  }
  steps
}

future::plan(future::multisession, workers = 4)
steps <- furrr::future_map(
  starts,
  \(x) find_steps(x, map_df, dirs)
)

options(digits = 22)
reduce(steps, pracma::Lcm)
