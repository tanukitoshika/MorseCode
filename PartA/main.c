
#include <xmc_gpio.h>
#include <stdio.h>
#include <string.h>

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 100
#define TICKS_WAIT2 300

#define LED1 P1_1
#define LED2 P1_0

// converts ascii-characters into morse code
char code[100];
int32_t j = 0;
char letter;

void ascii_to_morse(char character)
{
  switch (character)
  {

    // letters

  case 'a':
  case 'A':
    strcat(code, ".- ");
    break;

  case 'b':
  case 'B':
    strcat(code, "-... ");
    break;

  case 'c':
  case 'C':
    strcat(code, "-.-. ");
    break;

  case 'd':
  case 'D':
    strcat(code, "-.. ");
    break;

  case 'e':
  case 'E':
    strcat(code, ". ");
    break;

  case 'f':
  case 'F':
    strcat(code, "..-. ");
    break;

  case 'g':
  case 'G':
    strcat(code, "--. ");
    break;

  case 'h':
  case 'H':
    strcat(code, ".... ");
    break;

  case 'i':
  case 'I':
    strcat(code, ".. ");
    break;

  case 'j':
  case 'J':
    strcat(code, ".--- ");
    break;

  case 'k':
  case 'K':
    strcat(code, "-.- ");
    break;

  case 'l':
  case 'L':
    strcat(code, ".-.. ");
    break;

  case 'm':
  case 'M':
    strcat(code, "-- ");
    break;

  case 'n':
  case 'N':
    strcat(code, "-. ");
    break;

  case 'o':
  case 'O':
    strcat(code, "--- ");
    break;

  case 'p':
  case 'P':
    strcat(code, ".--. ");
    break;

  case 'q':
  case 'Q':
    strcat(code, "--.- ");
    break;

  case 'r':
  case 'R':
    strcat(code, ".-. ");
    break;

  case 's':
  case 'S':
    strcat(code, "... ");
    break;

  case 't':
  case 'T':
    strcat(code, "- ");
    break;

  case 'u':
  case 'U':
    strcat(code, "..- ");
    break;

  case 'v':
  case 'V':
    strcat(code, "...- ");
    break;

  case 'w':
  case 'W':
    strcat(code, ".-- ");
    break;

  case 'x':
  case 'X':
    strcat(code, "-..- ");
    break;

  case 'y':
  case 'Y':
    strcat(code, "-.-- ");
    break;

  case 'z':
  case 'Z':
    strcat(code, "--.. ");
    break;

    // spaces

  case ' ':
    strcat(code, "  ");
    break;

    // numbers

  case '0':
    strcat(code, "----- ");
    break;

  case '1':
    strcat(code, ".---- ");
    break;

  case '2':
    strcat(code, "..--- ");
    break;

  case '3':
    strcat(code, "...-- ");
    break;

  case '4':
    strcat(code, "....- ");
    break;

  case '5':
    strcat(code, "..... ");
    break;

  case '6':
    strcat(code, "....- ");
    break;

  case '7':
    strcat(code, "...-- ");
    break;

  case '8':
    strcat(code, "..--- ");
    break;

  case '9':
    strcat(code, ".---- ");
    break;

    // punctuation marks

  case '.':
    strcat(code, ".-.-.- ");
    break;

  case ',':
    strcat(code, "--..-- ");
    break;

  case ':':
    strcat(code, "---... ");
    break;

  case ';':
    strcat(code, "-.-.-. ");
    break;

  case '?':
    strcat(code, "..--.. ");
    break;

  case '-':
    strcat(code, "-....- ");
    break;

  case '_':
    strcat(code, "..--.- ");
    break;

  case '(':
    strcat(code, "-.--. ");
    break;

  case ')':
    strcat(code, "-.--.- ");
    break;

  case '\'':
    strcat(code, ".----. ");
    break;

  case '=':
    strcat(code, "-...- ");
    break;

  case '+':
    strcat(code, ".-.-. ");
    break;

  case '/':
    strcat(code, "-..-. ");
    break;

  case '@':
    strcat(code, ".--.-. ");
    break;

  default:
    strcat(code, "........ ");
  }
}

void SysTick_Handler(void)
{
  static uint32_t ticks = 0;

  ticks++;
  switch (letter)
  {
  case '.':
    if (ticks == 1)
    {
      XMC_GPIO_ToggleOutput(LED1);
    }
    if (ticks == TICKS_WAIT)
    {
      XMC_GPIO_ToggleOutput(LED1);
    }
    if (ticks == TICKS_WAIT + 100)
    {
      ticks = 0;
      j++;
    }
    break;

  case '-':
    if (ticks == 1)
    {
      XMC_GPIO_ToggleOutput(LED1);
    }
    if (ticks == TICKS_WAIT2)
    {
      XMC_GPIO_ToggleOutput(LED1);
    }
    if (ticks == TICKS_WAIT2 + 100)
    {
      ticks = 0;
      j++;
    }
    break;

  case ' ':
    if (ticks == 200)
    {
      ticks = 0;
      j++;
    }
    break;

  case 0:
    if (ticks == 5000)
    {
      ticks = 0;
      j = 0;
    }
    break;

  default:
    break;
  }
}

// main translation function

void translate_to_morse(char text[])
{
  int length = strlen(text);
  int i;
  char character;

  for (i = 0; i < length; i++) // translation loop
  {
    character = text[i];

    ascii_to_morse(character); // converts characters to morse code
  }
  printf("\n%s", code);
}

void translate_to_led()
{
  int length = strlen(code);

  if (j < length)
  {
    letter = code[j];
  }
  else
  {
    letter = 0;
  }
}

int main(void)
{

  char text[100] = "I CAN MORSE";
  printf("%s", text);

  printf("\n");

  translate_to_morse(text); // main translation function

  XMC_GPIO_CONFIG_t config;

  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

  XMC_GPIO_Init(LED1, &config);

  /* System timer configuration */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while (1)
  {
    /* Infinite loop */
    translate_to_led();
  }
}
