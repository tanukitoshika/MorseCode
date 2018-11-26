
#include <xmc_gpio.h>
#include <xmc_eru.h>
#include <xmc_scu.h>
#include <stdio.h>
#include <string.h>
#include "VirtualSerial.h"

#define TICKS_PER_SECOND 100
#define TICKS_WAIT 10
#define TICKS_WAIT2 30

#define LED1 P1_1
#define LED2 P1_0
#define BUTTON1 P1_14
#define BUTTON2 P1_15

// converts ascii-characters into morse code
char code[100] = " ";
int32_t j = 0;
char letter = 0;
int32_t execution = 0;
uint32_t ticks = 0;
uint32_t tick2 = 0;
int length = 0;

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
  ticks++;
  tick2++;
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
    if (ticks == TICKS_WAIT + TICKS_WAIT)
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
    if (ticks == TICKS_WAIT2 + TICKS_WAIT)
    {
      ticks = 0;
      j++;
    }
    break;

  case ' ':
    if (ticks == TICKS_WAIT * 2)
    {
      ticks = 0;
      j++;
    }
    break;

  case 0:
    ticks = 0;
    j = 0;
    execution = 0;
    break;

  default:
    break;
  }
}

// main translation function

void translate_to_morse(char text[])
{
  int length_c = strlen(text);
  int i;
  char character;

  for (i = 0; i < length_c; i++) // translation loop
  {
    character = text[i];

    ascii_to_morse(character); // converts characters to morse code
  }
  printf("\n%s", code);
}

void translate_to_led()
{
  if (j < length)
  {
    letter = code[j];
  }
  else
  {
    letter = 0;
    j = 0;
    execution = 0;
  }
}

/* Clock configuration */
XMC_SCU_CLOCK_CONFIG_t clock_config = {
    .syspll_config.p_div = 2,
    .syspll_config.n_div = 80,
    .syspll_config.k_div = 4,
    .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
    .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
    .enable_oschp = true,
    .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
    .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
    .fsys_clkdiv = 1,
    .fcpu_clkdiv = 1,
    .fccu_clkdiv = 1,
    .fperipheral_clkdiv = 1};

void SystemCoreClockSetup(void)
{
  /* Setup settings for USB clock */
  XMC_SCU_CLOCK_Init(&clock_config);

  XMC_SCU_CLOCK_EnableUsbPll();
  XMC_SCU_CLOCK_StartUsbPll(2, 64);
  XMC_SCU_CLOCK_SetUsbClockDivider(4);
  XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

  SystemCoreClockUpdate();
}

int main(void)
{
  char text[100] = "I CAN MORSE";

  translate_to_morse(text); // main translation function
  length = strlen(code);

  uint16_t Bytes = 0;

  const XMC_GPIO_CONFIG_t out_config =
      {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
       .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
       .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM};
  const XMC_GPIO_CONFIG_t in_config =
      {.mode = XMC_GPIO_MODE_INPUT_PULL_DOWN,
       .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
       .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};

  XMC_GPIO_Init(LED1, &out_config);
  XMC_GPIO_Init(LED2, &out_config);
  XMC_GPIO_Init(BUTTON1, &in_config);
  XMC_GPIO_Init(BUTTON2, &in_config);
  USB_Init();

  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
  int32_t last_tick = 0;
  int32_t second_last_tick = 0;
  int d;
  int on = 0;

  while (1)
  {
    /* Check if data received */
    Bytes = CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface);

    while (Bytes > 0)
    {
      /* Send data back to the host */
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface,
                          CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface));
      --Bytes;
    }

    if (XMC_GPIO_GetInput(BUTTON1) == 0)
    {
      execution = 1;
      if (on == 0)
      {
        second_last_tick = last_tick;
        last_tick = tick2;
        d = last_tick - second_last_tick;
      }
      on = 1;
    }
    else
    {
      on = 0;
    }

    if (execution == 1)
    {
      translate_to_led();
    }
    else if (XMC_GPIO_GetInput(BUTTON2) == 0 && last_tick != 0 && d < TICKS_PER_SECOND)
    {
      execution = 1;
    }
    else
    {
      XMC_GPIO_SetOutputLow(LED1);
    }

    CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
  }
  return 0;
}
