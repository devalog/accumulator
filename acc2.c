#include <stdio.h>
#include <string.h>
#include <ctype.h>

// This menu-driven program displays values in various base representations 
// (binary, hexadecimal, octal, decimal)based on the current value of the 
// program’s accumulator. It also perform various bitwise and arithmetic operations. 

void add (short *acc, char mode);
void subtract (short *acc, char mode);
unsigned short get_binary_op (char *bin);
void convert_to_binary (short acc, char *bin);
short get_operand (char mode);
void print_acc (short acc);
char print_menu ();

// Prints out accumulator if the user inputs a negative binary number.
void convert_to_binary (short acc, char *bin) {

  printf ("\n**************************************\n");
  printf ("* Accumulator:                       *\n");
  printf ("*   Binary  :  ");

  int j;
  for (j = 0; j<16; j++) {
    int p = bin[j];
    if (j == 4 || j == 8 || j == 12){
      printf(" ");
    }
    printf("%c", p);
   }
   printf("   *\n");
  printf ("*   Hex     :  %04hX                  *\n", acc);
  printf ("*   Octal   :  %06ho                *\n", acc);
  printf ("*   Decimal :  %-9d             *\n", acc);
  printf ("**************************************\n");

}

// Converts a binary string to an unsigned short representation.
unsigned short get_binary_op (char *bin) {
  unsigned short total = 0;
  int power = 15;
  int i;
  for (i = 0; i<16; i++) {
    if (bin[i] == '1') {
      total = total + (1 << power);
    }
    power = power - 1;
  }

  return total;

}

// Receives a mode and reads in a value from the user in the specified mode.
short get_operand (char mode) {
  short user_input;

// pass in mode and print out number
  switch (mode) {
    case 'b':
      printf("Enter binary value: ");
      char bin[16];
      scanf("%s",bin);
      printf("%s\n", bin);
      if (strlen(bin) < 16) {
        int count = 16;
        int track;
        for (track = strlen(bin); track >= 0; track --){
          bin[count] = bin[track];
          bin[track] = 0;
          count = count - 1;
        }
      }

      user_input = get_binary_op(bin);
      if (user_input < 0) {
        convert_to_binary(user_input, bin);
      }
      else {
        print_acc(user_input);
      }
      break;
    case 'h':
      printf("Enter hex value: ");
      scanf ("%hX", &user_input);
      printf("%hX\n",user_input);
      break;
    case 'o':
      printf("Enter octal value: ");
      scanf ("%ho", &user_input);
      printf("%ho\n",user_input);
      break;
    // Facilitates conversion from binary to decimal when user wants to add, subtract, etc. 
    case '?':
      printf("Enter binary value: ");
      scanf("%s",bin);
      user_input = get_binary_op(bin);
      printf("%s\n", bin);
      break;
    default:
      printf("Enter decimal value: ");
      scanf ("%hd", &user_input);
      printf("%hd\n",user_input);
      break;
  }

  return user_input;

}

// Prints accumulator values for Binary (positive), Hex, Octal, and Decimal modes
void print_acc (short acc) {
  int negative = 0;
  int newacc = (int) acc;
  if (acc < 0) {
    negative = 1;
    newacc = newacc - (acc*2);
  }
  int binary [] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  short old_tot;
  int rem;
  int counter = 0;

  while (newacc != 0) {
    old_tot = newacc;
    newacc = newacc/2;
    rem = old_tot - (newacc*2); //append rem to array of char
    binary[15-counter]=rem;
    counter = counter + 1;
  }

  // if negative, convert binary bits (currenty in positive representation)
  if (negative == 1) {
    int i;
    for (i = 0; i<16; i++) {
      // reverse bits
      if (binary[i] == 1){
        binary[i] = 0;
      }
      else {
        binary[i] = 1;
      }
    }
    //add 1
    for (i = 15; i>=0; i--) {
      if (binary[i] == 1) {
        binary[i] = 0;
      }
      else if (binary[i] == 0) {
        binary[i] = 1;
        break;
      }
    }
  }

    printf ("\n**************************************\n");
    printf ("* Accumulator:                       *\n");
    printf ("*   Binary  :  ");

    int j;
    for (j = 0; j<16; j++) {
      int p = binary[j];
      if (j == 4 || j == 8 || j == 12){
        printf(" ");
      }
      printf("%d", p);
     }
     printf("   *");

  printf ("\n*   Hex     :  %04hX                  *\n", acc);
  printf ("*   Octal   :  %06ho                *\n", acc);
  printf ("*   Decimal :  %-9d             *\n", acc);
  printf ("**************************************\n");

}


// Prints the menu of user options
char print_menu () {
  char choice[10];

  printf ("\nPlease select one of the following options: \n\n");
  printf ("B  Binary Mode             &  AND with Accumulator           +  Add to Accumulator\n");
  printf ("O  Octal Mode              |  OR  with Accumulator           -  Subtract from Accumulator\n");
  printf ("H  Hexadecimal Mode        ^  XOR with Accumulator           N  Negate Accumulator\n");
  printf ("D  Decimal Mode            ~  Complement Accumulator\n");
  printf ("\nC  Clear Accumulator       <  Shift Accumulator Left\n");
  printf ("S  Set Accumulator         >  Shift Accumulator Right\n");
  printf ("\nQ  Quit \n");
  printf ("\nOption: ");

// Scan the user's selection into an array of char
  scanf (" %s", choice);
  printf("%s\n", choice);

  char option = toupper(choice[0]);

// Error checking on user's choice: must be one of the menu choices to continue
  if (strlen(choice)!= 1 || (option != 'O'&& option != 'H'
  && option != 'D' && option != 'C' && option != 'S'
  && option != 'Q' && option != 'B' && option != '&'
  && option != '|' && option != '^' && option != '~'
  && option != 'N' && option != '<' && option != '>'
  && option != '+' && option != '-') ) {

    printf ("Invalid option: %s\n", choice);
    return 'I';
  }

  else {
    return option;
  }

}

// Subtract from current accumulator value
void subtract (short *acc, char mode) {
  short op;
  short save_acc;
  save_acc = *acc;

  if (mode == 'b') {
    mode = '?';
    op = get_operand(mode);
    *acc = *acc - op;
  }
  else {
    op = get_operand(mode);
    *acc= *acc - op;
  }
  if (save_acc > 0 && *acc < 0) {
    printf("Overflow Error\n");
  }
  else if (save_acc < 0 && *acc > 0) {
    printf("Negative Overflow Error\n");
  }

  print_acc(*acc);


}

// Add to current accumulator value
void add (short *acc, char mode){
  short op;
  short save_acc;
  save_acc = *acc;

  if (mode == 'b') {
    mode = '?';
    op = get_operand(mode);
    *acc = *acc + op;
  }
  else {
    op = get_operand(mode);
    *acc = *acc + op;
  }
  if (save_acc > 0 && *acc < 0) {
    printf("Overflow Error\n");
  }
  else if (save_acc < 0 && *acc > 0) {
    printf("Negative Overflow Error\n");
  }
  print_acc(*acc);

}

// Run the program.
int main () {
  short input;
  int shift = 0;
  short save_acc;
  int quit_tracker = 0;
  short acc_value = 0;
  print_acc(acc_value);
  char save_mode;

  while (quit_tracker == 0) {
    short selected_option = print_menu();
    char mode;

 // Changes the mode according to the user's choice.
   switch (selected_option) {
  case 'B':
    printf ("Mode is Binary\n");
    mode = 'b';
    print_acc(acc_value);
    break;

  case 'O': printf ("Mode is Octal\n");
     mode = 'o';
     print_acc(acc_value);
     break;

   case 'H': printf ("Mode is Hexadecimal\n");
     mode = 'h';
     print_acc(acc_value);
     break;

   case 'D': printf ("Mode is Decimal\n");
     mode = 'd';
     print_acc(acc_value);
     break;

  case '&':
    save_mode = mode;
    if (mode == 'b') {
      mode = '?';
    }
    input = get_operand(mode);
    acc_value = acc_value & input;
    print_acc(acc_value);
    mode = save_mode;
    break;

  case '|':
  save_mode = mode;
  if (mode == 'b') {
    mode = '?';
  }
  input = get_operand(mode);
  acc_value = acc_value | input;
  print_acc(acc_value);
  mode = save_mode;
    break;

  case '^':
  save_mode = mode;
  if (mode == 'b') {
    mode = '?';
  }
  input = get_operand(mode);
  acc_value = acc_value ^ input;
  print_acc(acc_value);
  mode = save_mode;
    break;

  case '<':
    printf("Enter number of positions to left shift accumulator: ");
    scanf ("%d", &shift);
    printf ("%d\n", shift);
    acc_value = acc_value << shift;
    print_acc(acc_value);
    break;

  case '>':
    printf("Enter number of positions to right shift accumulator: ");
    scanf ("%d", &shift);
    printf ("%d\n", shift);
    acc_value = acc_value >> shift;
    print_acc(acc_value);
    break;

  case '~':
    acc_value = ~acc_value;
    print_acc(acc_value);
    break;

  case 'N':
    acc_value = ~acc_value + 1;
    print_acc(acc_value);
    break;

  case '+':
    add(&acc_value, mode);
    break;

  case '-':
    subtract(&acc_value, mode);
    break;

// Clear the accumulator
   case 'C':
     acc_value = 0;
     print_acc(acc_value);
     break;

// Set the accumulator
   case 'S':
     acc_value = get_operand(mode);
     if (mode != 'b') {
       print_acc(acc_value);
     }
     break;

   case 'Q':
     quit_tracker = 1;
     break;

   default:
     break;
   }

 }
  return 0;

}
