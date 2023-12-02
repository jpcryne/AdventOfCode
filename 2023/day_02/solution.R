# * Format Data
input <- read.delim(here::here("2023/day_02/input.txt"), sep = ";", header = FALSE) |>
  tidyr::separate(col = V1, sep = ":", into = c("id", "V1")) |>
  dplyr::mutate(id = as.integer(gsub("^Game ", "", id)))

game_cols <- grep("^V", names(input), value = TRUE)

input_long <- input |>
  tidyr::pivot_longer(cols = dplyr::all_of(game_cols), names_pattern = "V(\\d)") |>
  dplyr::mutate(
    blue = stringr::str_extract(value, "\\d+ blue") |> stringr::str_replace(" blue", ""),
    red = stringr::str_extract(value, "\\d+ red") |> stringr::str_replace(" red", ""),
    green = stringr::str_extract(value, "\\d+ green") |> stringr::str_replace(" green", ""),
    dplyr::across(c(red, green, blue), \(x) as.integer(dplyr::if_else(is.na(x), "0", x)))
  )

# * Part 1
input_long |>
  dplyr::summarise(
    possible = all(red <= 12 & green <= 13 & blue <= 14),
    .by = c(id)
  ) |>
  dplyr::summarise(sum(id * possible))

# * Part 2
input_long |>
  dplyr::summarise(
    power = max(red) * max(blue) * max(green),
    .by = c(id)
  ) |>
  dplyr::summarise(
    sum(power)
  )
