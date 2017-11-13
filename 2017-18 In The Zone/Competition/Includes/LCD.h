menu *defaultMenu, *autonMenu, *sensorMenu, *batteryMenu;

void configLCD()
{
	defaultMenu = lcd_newMenu("HOW'S MY DRIVING?", "1-800-GFR-5327B");
	autonMenu = lcd_newMenu("Autons");
	sensorMenu = lcd_newMenu("Sensors");
	batteryMenu = lcd_newMenu("Battery");
	lcd_linkMenus(autonMenu, sensorMenu, batteryMenu);
	lcd_formLevel(defaultMenu, autonMenu, sensorMenu, batteryMenu);
	startTask(lcdControlTask);
}

void lcd_invoke(int func)
{
	switch (func)
	{
	case 0:
		break;
	default:
		break;
	}
}
