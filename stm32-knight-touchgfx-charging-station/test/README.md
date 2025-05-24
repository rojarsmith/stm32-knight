# Test Case

## Test Communication on Simulator
You can test communication of business logic with modfying the debug_input_data.json file and watch the output data send from UX with the debug_output_data.json file. Wait until the screen at screen 2.0 begin to test business logic.

Notice that some parameter need to be rising or falling edge to trigger the business logic.

-debug_input_data.json

outside ===> UX

-debug_output_data.json

outside <=== UX

### Test Case
Just sample part of business logic, not completely.
1. Pay by QR code

Screen 2.0 drag to right side -> Screen 3.0 click QR code label -> checking circle was rotation -> "ux_payment_selector"=>1 -> Screen 4.0 "ux_plugin_in_out_status_right"=>1, "ux_plugin_usability_status_right"=>1

2. Pay by RFID at 2.0

Screen 2.0 "ux_home_rfid_status"=>2 -> Screen 4.0 "ux_home_rfid_status"=>4 -> checking circle was shown "V" -> "ux0400_plug_right_status"=>2 -> Screen 4.0 "ux_plugin_in_out_status_right"=>1, "ux_plugin_usability_status_right"=>1

3. Call popups
At any screen set "ux_popup_number" number.

4. Change day/night
At any screen set "ux_weather" number.
