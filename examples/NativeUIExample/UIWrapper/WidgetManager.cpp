/*
Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file WidgetManager.cpp
 * @author Mikael Kindborg
 *
 * The WidgetManager is the heart of the widget system
 * It has methods for creating widgets, and manages widget
 * events and dispatches them to the target widgets.
 */

#include "WidgetManager.h"

namespace MoSync
{
	namespace UI
	{

	/**
	 * Constructor.
	 */
	WidgetManager::WidgetManager()
	{
		// Add me as a custom event listener.
		MAUtil::Environment::getEnvironment().addCustomEventListener(this);
	}

	/**
	 * Destructor.
	 */
	WidgetManager::~WidgetManager()
	{
	}

	/**
	 * Create a screen widget.
	 * @return A screen widget.
	 */
	Screen* WidgetManager::createScreen()
	{
		MAHandle widgetHandle = maWidgetCreate(MAW_SCREEN);
		checkNativeUISupport(widgetHandle);
		Screen* widget = new Screen(widgetHandle, this);
		addWidgetToMap(widgetHandle, widget);
		return widget;
	}

	/**
	 * Create a horizontal layout. By default,
	 * this layout fills the parent space.
	 * @return An horizontal layout widget.
	 */
	Layout* WidgetManager::createHorizontalLayout()
	{
		MAHandle widgetHandle = maWidgetCreate(MAW_HORIZONTAL_LAYOUT);
		checkNativeUISupport(widgetHandle);
		Layout* widget = new Layout(widgetHandle, this);
		addWidgetToMap(widgetHandle, widget);
		widget->fillSpaceVertically();
		widget->fillSpaceHorizontally();
		widget->setBackgroundColor(255, 255, 255);
		return widget;
	}

	/**
	 * Create a vertical layout. By default,
	 * this layout fills the parent space.
	 * @return An vertical layout widget.
	 */
	Layout* WidgetManager::createVerticalLayout()
	{
		MAHandle widgetHandle = maWidgetCreate(MAW_VERTICAL_LAYOUT);
		checkNativeUISupport(widgetHandle);
		Layout* widget = new Layout(widgetHandle, this);
		addWidgetToMap(widgetHandle, widget);
		widget->fillSpaceVertically();
		widget->fillSpaceHorizontally();
		return widget;
	}

	/**
	 * Create a button widget.
	 * @return A button widget.
	 */
	Button* WidgetManager::createButton()
	{
		MAHandle widgetHandle = ::maWidgetCreate(MAW_BUTTON);
		checkNativeUISupport(widgetHandle);
		Button* widget = new Button(widgetHandle, this);
		addWidgetToMap(widgetHandle, widget);
		widget->fillSpaceHorizontally();
		widget->wrapContentVertically();
		widget->setText("Click Me!");
		widget->centerTextHorizontally();
		widget->centerTextVertically();
		return widget;
	}

	/**
	 * Implementation of CustomEventListener interface.
	 * This method will get called whenever there is a
	 * widget event generated by the system.
	 */
	void WidgetManager::customEvent(const MAEvent& event)
	{
		// Check if this is a widget event.
		if (EVENT_TYPE_WIDGET == event.type)
		{
			// Get the widget event data structure.
			MAWidgetEventData* eventData = (MAWidgetEventData*) event.data;

			// Check if the widget exists in the map.
			if (mWidgetMap.end() != mWidgetMap.find(eventData->widgetHandle))
			{
				// Get the widget object that wraps the widget handle.
				Widget* widget = mWidgetMap[eventData->widgetHandle];

				// Call the widge's event handling method.
				widget->handleWidgetEvent(eventData);
			}
		}
	}

	/**
	 * Error handling for devices that do not support NativeUI.
	 * Here we throw a panic if NativeUI is not supported.
	 */
	void WidgetManager::checkNativeUISupport(int result)
	{
		if (-1 == result)
		{
			maPanic(0,
				"NativeUI is only available on Android and iPhone. "
				"You must run directly on the device or devices emulator.");
		}

	}

	/**
	 * Add a widget to the map that holds widget objects.
	 */
	void WidgetManager::addWidgetToMap(MAHandle widgetHandle, Widget* widget)
	{
		mWidgetMap[widgetHandle] = widget;
	}

	} // namespace UI
} // namespace MoSync
