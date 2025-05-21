#include <platform/hal/simulator/sdl2/HALSDL2.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <common/TouchGFXInit.hpp>
#include <gui_generated/common/SimConstants.hpp>
#include <platform/driver/touch/SDL2TouchController.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <stdlib.h>
#include <simulator/mainBase.hpp>
#include <touchgfx/Utils.hpp>

using namespace touchgfx;

static const int dynamic_bitmap_buffer_size = 768 * 1024 * 4 * 4;
static uint8_t dynamic_bitmap_buffer[dynamic_bitmap_buffer_size];

#ifdef __linux__
int main(int argc, char** argv)
{
#else
#include <shellapi.h>
#ifdef _UNICODE
#error Cannot run in unicode mode
#endif
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc;
    char** argv = touchgfx::HALSDL2::getArgv(&argc);
#endif

    touchgfx::NoDMA dma; //For windows/linux, DMA transfers are simulated
    LCD& lcd = setupLCD();
    touchgfx::SDL2TouchController tc;
                                                                                                                          // bitmapCache, bitmapCacheSize, numberOfDynamicBitmaps
    touchgfx::HAL& hal = touchgfx::touchgfx_generic_init<touchgfx::HALSDL2>(dma, lcd, tc, SIM_WIDTH, SIM_HEIGHT, (uint16_t*)dynamic_bitmap_buffer, dynamic_bitmap_buffer_size, 7);
    //touchgfx::HAL& hal = touchgfx::touchgfx_generic_init<touchgfx::HALSDL2>(dma, lcd, tc, SIM_WIDTH, SIM_HEIGHT, 0, 0);

    setupSimulator(argc, argv, hal);

    // Ensure there is a console window to print to using printf() or
    // std::cout, and read from using e.g. fgets or std::cin.
    // Alternatively, instead of using printf(), always use
    // touchgfx_printf() which will ensure there is a console to write
    // to.
    touchgfx_enable_stdio();

    //touchgfx::HAL::getInstance()->setDisplayOrientation(ORIENTATION_PORTRAIT);
    touchgfx::HAL::getInstance()->setFrameRateCompensation(true);

    // Print out size information
    printf("*** Memory usage: ***\r\n");
    printf("Largest view      %lu\r\n", (long unsigned int) sizeof(FrontendHeap::MaxViewType));
    printf("Largest presenter %lu\r\n", (long unsigned int) sizeof(FrontendHeap::MaxPresenterType));
    printf("Datamodel         %lu\r\n", (long unsigned int) sizeof(Model));
    printf("Total:            %lu\r\n", (long unsigned int) sizeof(FrontendHeap));
    printf("*** Screens: ***\r\n");
    printf("Main Screen       %lu\r\n", (long unsigned int) sizeof(HomeView));

    touchgfx::HAL::getInstance()->taskEntry(); //Never returns

    return EXIT_SUCCESS;
}
