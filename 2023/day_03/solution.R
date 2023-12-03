input <- read.delim(here::here("2023/day_03/input.txt"), sep = "", header = FALSE) |>
  dplyr::mutate(row = dplyr::row_number())

# * Extract number locations
num_loc <- input |>
  dplyr::reframe(
    locs = V1 |> stringr::str_locate_all("\\d+") |> getElement(1),
    number = V1 |> stringr::str_extract_all("\\d+") |> getElement(1) |> as.integer(),
    .by = c(row)
  ) |>
  dplyr::mutate(
    id = dplyr::row_number(), 
    col = purrr::map2(locs[, 1], locs[, 2], seq)
  ) |>
  tidyr::unnest(col) |>
  dplyr::select(id, row, col, number)

sym_loc <- input |>
  dplyr::reframe(
    locs = V1 |> stringr::str_locate_all("[^0-9\\.]") |> getElement(1),
    symbol = V1 |> stringr::str_extract_all(pattern = "[^0-9\\.]") |> getElement(1),
    col = locs[, 1],
    .by = c(row)
  ) |>
  dplyr::select(-locs)

# * Part 1
num_loc |>
  dplyr::cross_join(sym_loc, suffix = c(".num", ".sym")) |>
  dplyr::filter(
    row.num <= row.sym + 1,
    row.num >= row.sym - 1,
    col.num <= col.sym + 1,
    col.num >= col.sym - 1
  ) |>
  dplyr::summarise(
    number = dplyr::first(number), .by = c(id)
  ) |>
  dplyr::summarise(sum(number))

# * Part 2
num_loc |>
  dplyr::cross_join(sym_loc, suffix = c(".num", ".sym")) |>
  dplyr::filter(
    row.num <= row.sym + 1,
    row.num >= row.sym - 1,
    col.num <= col.sym + 1,
    col.num >= col.sym - 1
  ) |>
  dplyr::filter(symbol == "*") |>
  dplyr::filter(dplyr::n_distinct(id) == 2, .by = c(row.sym, col.sym)) |>
  dplyr::summarise(number = dplyr::first(number), .by = c(id, row.sym, col.sym)) |>
  dplyr::summarise(gear_ratio = prod(number), .by = c(row.sym, col.sym)) |>
  dplyr::summarise(sum(gear_ratio))

