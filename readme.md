# Bitgrinder
Bitgrinder is a cryptocurrency trading bot written in C++ designed to perform a number of different types of trades at high speed.




# Prerequisites

Bitgrinder
-
1. libcurl4-openssl-dev
2. boost_1_54_0 (can upgrade to new version)
# Exchanges

Gate.io
-
Server time is GMT+8 : Shanghai, Beijing, Philippines, West Australia
Unix timestamp requires no conversion.

Trade Data Model
-
Works in 30 day increments made up of 5 minute periods (the smallest increment). Each 5 minute period is combined with other related periods for analysis for 10 minute, 15 minute, 30 minute and 60 minute windows for analysis.

# TODO:
1. Move data model to a memory-based (only) model
2. Implement periods, drop periods older than 30 days
3. Perform basic analysis on periods
4. Implement data export to save startup time
