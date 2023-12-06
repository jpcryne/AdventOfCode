input_raw <- read.delim(here::here("2023/day_05/input.txt"), header = FALSE, sep = "\n")

# * Extract seeds
extract_int <- function(x) {
  stringr::str_extract_all(x, pattern = "\\d+") |>
    unlist() |>
    as.numeric()
}
seeds <- extract_int(input_raw$V1[1])

run <- function(input, seeds) {
  input_layer <- seeds
  for (row in 2:nrow(input)) {
    row_content <- input_raw$V1[row]
    
    if (grepl("map:", row_content)) {
      mapped_values <- rep(NA, length(seeds))
      next
    }
    
    # * Extract the numbers that define the map
    map_def <- extract_int(row_content)
    for (i in 1:length(input_layer)) {
      x <- input_layer[i]
      if (x >= map_def[2] && x < map_def[2] + map_def[3] && is.na(mapped_values[i])) {
        mapped_values[i] <- map_def[1] + (x - map_def[2])
      }
    }
    input_layer <- dplyr::coalesce(mapped_values, input_layer)
  }
  input_layer
}

# * Part 1
run(input_raw, seeds) |>
  min()

# * Part 2
seeds2 <- seeds |>
  matrix(nrow = 2) |>
  t() |>
  as.data.frame()

library(parallel)
library(furrr)
library(future)

plan(multisession, workers = 8)

run_mins <- c()
for (i in 1:nrow(seeds2)) {
  cat(i, " / ", 10, "\n")
  range_start <- seeds2$V1[i]
  range_end <- seeds2$V2[i]
  range_list <- split(seq.int(0, range_end - 1), 1:1000)
  run_min <- future_map(
    range_list,
    \(x) {
      run(input_raw, range_start + x) |>
        min()
    },
    .progress = TRUE
  ) |>
    unlist() |>
    min()
  print(run_min)
  run_mins <- c(run_mins, run_min)
}
min(run_mins)
