GREEN="\e[0;32m"
PURPLE="\033[35m"
RED="\033[31m"
BLUE='\033[36m'
BOLD="\033[1m"
STD="\033[0m"

Print_message() {
  printf "$1$BOLD%s" "$2"
  echo "$STD"
}

echo
Print_message "$STD" "Run tests for STL containers..."
Print_message "$STD" "Run the same tests for my containers..."
Print_message "$GREEN" "Comparing results..."
Print_message "$BLUE" "The difference between two tests is:"

diff "$1"my_out "$1"std_out

echo
Print_message "$BLUE" "If there are no output above, all tests passed ✅"
