#include <iostream>

using namespace std;

const int MAX_ROW_ARRAY = 6;
const int MAX_COL_ARRAY = 7;
const int MAX_ROW_PRINT = 8;
const int MAX_COL_PRINT = 15;
const int TOTAL_POSIBLE_MOVES = 42 / 2; // Each player will have maximum of 21 possible moves

void clear_board(char board[][MAX_COL_ARRAY]);
void print_top_bottom_board(void);
void print_board(char board[][MAX_COL_ARRAY]);
void print_middle_of_board(char board[][MAX_COL_ARRAY]);
void prompt_player_1_choose(void);
void prompt_player_2_choose(void);
int get_player_input(void);
int check_player_input(int player_input,char board[][MAX_COL_ARRAY]);
void assign_value_player_1(int check_input_result, char board[][MAX_COL_ARRAY]);
void assign_value_player_2(int check_input_result, char board[][MAX_COL_ARRAY]);
bool ready_to_check(char board[][MAX_COL_ARRAY]);
char check_collum_smilarity(char board[][MAX_COL_ARRAY]);
char check_row_similarity(char board[][MAX_COL_ARRAY]);
char check_diagonal_right_to_left(char board[][MAX_COL_ARRAY]);
char check_who_win(char board[][MAX_COL_ARRAY]);
char check_diagonal_left_to_right(char board[][MAX_COL_ARRAY]);

int main(void)
{
	cout << "This is Connect by 4 game" << endl;
	cout << "Enter the collumn number you choose then press enter" << endl;
	char play_again = 'y';

	do
	{
		char connect_four_board[MAX_ROW_ARRAY][MAX_COL_ARRAY];
	
		clear_board(connect_four_board);

		print_board(connect_four_board);
		for (int move_counter = 0; move_counter < TOTAL_POSIBLE_MOVES; ++move_counter)
		{
			prompt_player_1_choose();
			assign_value_player_1(check_player_input(get_player_input(),connect_four_board),connect_four_board);
		
			print_board(connect_four_board);
		
			if (check_who_win(connect_four_board) != NULL)
			{
				cout << "player with colour " << check_who_win(connect_four_board) << " win" << endl;
				break;
			}

			prompt_player_2_choose();
			assign_value_player_2(check_player_input(get_player_input(),connect_four_board),connect_four_board);

			print_board(connect_four_board);

			if (check_who_win(connect_four_board) != NULL)
			{
				cout << "player with colour " << check_who_win(connect_four_board) << " win" << endl;
				break;
			}

		}
		if (check_who_win(connect_four_board) == NULL)
		{
			cout << "Bummer the match is draw" << endl;
		}
		
		cout << "Wanna play again (y/n)? ";
	
		cin >> play_again;
	
	} while (play_again == 'y');

	cout << "Goodbye player" << endl;

	return 0;
}
void clear_board(char board[][MAX_COL_ARRAY])
{
	for (int row_element = 0; row_element < MAX_ROW_ARRAY; ++row_element)
	{
		for (int col_number = 0; col_number < MAX_COL_ARRAY; ++col_number)
		{
			board[row_element][col_number] = '\0';
		}
	}	
}
void print_board(char board [][MAX_COL_ARRAY])
{
	cout << " 1 2 3 4 5 6 7" << endl;
	print_top_bottom_board();
	print_middle_of_board(board);
	print_top_bottom_board();
}
void print_top_bottom_board(void)
{
	for (int printed_char = 0; printed_char < MAX_COL_PRINT; ++printed_char)
	{
		if (printed_char % 2 == 0)
		{
			cout << "+";
		}
		else
		{
			cout << "-";
		}
	}
	cout << endl;
}
void print_middle_of_board(char board[][MAX_COL_ARRAY])
{
	int gap_between_print_and_array = 1;

	//to access element of the array, we have to subjact col_printed by the gap 
	for (int printed_row = 0; printed_row < MAX_ROW_PRINT - 2; ++printed_row)
	{
		gap_between_print_and_array = 1;
		for (int col_printed = 0; col_printed < MAX_COL_PRINT; ++col_printed)
		{
			if (col_printed % 2 == 0)
			{
				cout << "|";
			}
			else
			{
				cout << board[printed_row][col_printed - gap_between_print_and_array];
				++gap_between_print_and_array;
			}
		}
		cout << endl;
	}
}
void prompt_player_1_choose(void)
{
	cout << "Player 1 your colour is Red so it will show as R on the board" << endl;
	cout << "Please choose your collum ";
}
void prompt_player_2_choose(void)
{
	cout << "Player 2 your colour is Blue so it will show as B on the board" << endl;
	cout << "Please choose your collum ";
}
int get_player_input(void)
{
	int user_input;
	cin >> user_input;
	
	return user_input - 1;
}
int check_player_input(int player_input, char board[][MAX_COL_ARRAY])
{
	if (board[0][player_input] != NULL || player_input > 9 || player_input < 0)
	{
		if (board[0][player_input] != NULL)
		{
			cout << "The collumn is full, please choose other collum: ";
		}
		else
		{
			cout << "Invalid collumn number,please enter again: ";
		}
		player_input = check_player_input(get_player_input(),board);
	}
	return player_input;
}
void assign_value_player_1(int check_input_result, char board[][MAX_COL_ARRAY])
{
	int assigned_value = 0;
	for (int row_position = MAX_ROW_ARRAY - 1; row_position >= 0 && assigned_value == 0; --row_position)
	{
		if (board[row_position][check_input_result] == NULL)
		{
			board[row_position][check_input_result] = 'R';
			++assigned_value;
		}
	}
}
void assign_value_player_2(int check_input_result, char board[][MAX_COL_ARRAY])
{
	int assigned_value = 0;
	for (int row_position = MAX_ROW_ARRAY - 1; row_position >= 0 && assigned_value == 0; --row_position)
	{
		if (board[row_position][check_input_result] == NULL)
		{
			board[row_position][check_input_result] = 'B';
			++assigned_value;
		}
	}
}
bool ready_to_check(char board[][MAX_COL_ARRAY])
{
	int element_filled = 0;
	for (int col = 0; col < MAX_COL_ARRAY; ++col)
	{
		if (board[2][col] != NULL)
		{
			++element_filled;
		}
	}

	if (element_filled > 0) 
	{
		return true;
	}
	else
	{
		return false;
	}
}
char check_collum_smilarity(char board[][MAX_COL_ARRAY])
{
	char check_value = NULL;
	int number_of_similarity = 0;

	for (int row = MAX_ROW_ARRAY - 1; row >= 3; --row)
	{
		for (int col = 0; col < MAX_COL_ARRAY; ++col)
		{
			check_value = board[row][col];
			number_of_similarity = 0;

			for (int start_check_at_row = row; start_check_at_row >= row - 3; --start_check_at_row)
			{
				if (board[start_check_at_row][col] != NULL && board[start_check_at_row][col] == check_value)
				{
					++number_of_similarity;
				}

				if (number_of_similarity == 4)
				{
					return check_value;
				}
			}
		}
	}
	return NULL;
}
char check_row_similarity(char board[][MAX_COL_ARRAY])
{
	char check_value = NULL;
	int number_of_similarity = 0;

	for (int row = MAX_ROW_ARRAY - 1; row <= 0; ++row)
	{
		for (int col_start = 0; col_start < 4; ++col_start)
		{
			check_value = board[row][col_start];
			number_of_similarity = 0;

			for (int col_check = col_start; col_check < col_start + 4; ++col_check)
			{
				if (check_value == board[row][col_check] && board[row][col_check] != NULL)
				{
					++number_of_similarity;
				}
				if (number_of_similarity == 4)
				{
					return check_value;
				}
			}
		}
	}
	return NULL;
}
char check_who_win(char board[][MAX_COL_ARRAY])
{
	char win_colour[4];

	win_colour[0] = check_collum_smilarity(board);
	win_colour[1] = check_row_similarity(board);
	win_colour[2] = check_diagonal_right_to_left(board);
	win_colour[3] = check_diagonal_left_to_right(board);

	for (int checked_element = 0; checked_element < 4; ++checked_element)
	{
		if (win_colour[checked_element] != NULL)
		{
			return win_colour[checked_element];
		}
	}
	return NULL;
}
char check_diagonal_right_to_left(char board[][MAX_COL_ARRAY])
{
	char compare = 0;
	int similarity_counter = 0;

	for (int starting_row = 0, end_row = 3; starting_row < 3; ++starting_row, ++end_row)
	{
		for (int start_col = 3; start_col < MAX_COL_ARRAY; ++start_col)
		{
			compare = board[starting_row][start_col];
			similarity_counter = 0;

				for (int row_check_at = starting_row, col_check_at = start_col; row_check_at < (starting_row + 4); ++row_check_at, --col_check_at)
				{
				if (board[row_check_at][col_check_at] == compare && board[row_check_at][col_check_at] != NULL )
				{
					++similarity_counter;
				}
				if (similarity_counter == 4)
				{
					return board[row_check_at][col_check_at];
				}
			}
		}
	}
	return NULL;
}
char check_diagonal_left_to_right(char board[][MAX_COL_ARRAY])
{
	char compare = 0;
	int similarity_counter = 0;

	for (int start_checking_row = 0; start_checking_row < 3; ++start_checking_row)
	{
		for (int start_checking_col = 0; start_checking_col < 4; ++start_checking_col)
		{
			compare = board[start_checking_row][start_checking_col];
			similarity_counter = 0;

			for (int col_check_start_at = start_checking_col, row_check_start_at = start_checking_row; col_check_start_at < start_checking_col + 4; ++col_check_start_at,++row_check_start_at)
			{
				if (board[row_check_start_at][col_check_start_at] != NULL && board[row_check_start_at][col_check_start_at] == compare)
				{
					++similarity_counter;
				}
				if (similarity_counter == 4)
				{
					return compare;
				}

			}
		}
	}
	return NULL;
}