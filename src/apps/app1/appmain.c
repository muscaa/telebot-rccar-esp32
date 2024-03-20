/*
#1. Meeting rooms reservation system

The user can view the available rooms and book a room.
The app allows adding/deleting a room with name and capacity,
displaying all rooms and bookings, searching for a room by name,
capacity and availability, booking the room and canceling the booking.
To book a room, the user must specify the date and time.
*/

#include "appmain.h"

#include "appmenus.h"
#include "rooms.h"

/*private int menu_rooms();
    private int menu_rooms_view();
        private int menu_rooms_view_availablerooms(int rooms_length, room (*get_room)(int));
            private int menu_room_info(room room);
                private int menu_room_bookings(room room, int (*back)());
        private int menu_rooms_view_filter();
            private void menu_name_filter(name_filter* filter);
            private void menu_capacity_filter(capacity_filter* filter);
            private void menu_availability_filter(availability_filter* filter);
                private bool menu_date_time_picker(date* date_from, time* time_from, date* date_to, time* time_to);
    private int menu_rooms_add();
private int menu_bookings();
    private int menu_booking_info(room room, booking booking);

private int menu_booking_info(room room, booking booking) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                ->name(format("Booking from: %02d/%02d/%04d %02d:%02d",
                        booking.date_from.day, booking.date_from.month, booking.date_from.year, booking.time_from.hour, booking.time_from.minute))
                ->build(),
        builder_separator()
                ->name(format("Booking to: %02d/%02d/%04d %02d:%02d",
                        booking.date_to.day, booking.date_to.month, booking.date_to.year, booking.time_to.hour, booking.time_to.minute))
                ->build(),
        SEPARATOR,
        builder_selection("Cancel")
                ->id(2)
                ->build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id == 2) {
        cancel_booking(room, booking);
        return menu_rooms_view();
    }
    return action_performed(actions, opt);
}

private int menu_room_bookings(room room, int (*back)()) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(back),
        BACK_TO_MAIN_MENU,
    };
    int i = 0;
    option options[room.bookings_length + 5];
    options[i++] = TITLE;
    options[i++] = SEPARATOR;
    for (; i < room.bookings_length + 2; i++) {
        booking b = room.bookings[i - 2];
        options[i] = builder_selection(format("(%02d/%02d/%04d %02d:%02d - %02d/%02d/%04d %02d:%02d)",
                                b.date_from.day, b.date_from.month, b.date_from.year, b.time_from.hour, b.time_from.minute,
                                b.date_to.day, b.date_to.month, b.date_to.year, b.time_to.hour, b.time_to.minute))
                        ->id(i)
                        ->build();
    }
    if (room.bookings_length == 0) {
        options[i++] = builder_separator()
                        ->name("No bookings.")
                        ->build();
    }
    options[i++] = SEPARATOR;
    options[i++] = option_selection_action(actions, &actions_index);
    options[i++] = option_selection_action(actions, &actions_index);
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id >= 2) {
        return menu_booking_info(room, room.bookings[opt->id - 2]);
    }
    return action_performed(actions, opt);
}

private int menu_room_info(room room) {
    int actions_index = 0;
    program_action actions[] = {
        BACK_TO(menu_rooms_view),
        BACK_TO_MAIN_MENU,
    };
    option options[] = {
        TITLE,
        SEPARATOR,
        builder_separator()
                ->name(format("Room name: %s", room.name))
                ->build(),
        builder_separator()
                ->name(format("Room capacity: %d", room.capacity))
                ->build(),
        SEPARATOR,
        builder_selection(format("Bookings (%d)", room.bookings_length))
                ->id(2)
                ->build(),
        builder_selection("Book")
                ->id(3)
                ->build(),
        builder_selection("Delete")
                ->id(4)
                ->build(),
        SEPARATOR,
        option_selection_action(actions, &actions_index),
        option_selection_action(actions, &actions_index),
    };
    option opt = vmenu(sizeof(options) / sizeof(option), options);
    if (opt->id == 2) {
        return menu_room_bookings(room, menu_rooms_view);
    } else if (opt->id == 3) {
        date date_from;
        time time_from;
        date date_to;
        time time_to;

        if (menu_date_time_picker(&date_from, &time_from, &date_to, &time_to)) {
            book_room(room, date_from, time_from, date_to, time_to);
        }
        
        return menu_rooms_view();
    } else if (opt->id == 4) {
        delete_room(room);
        return menu_rooms_view();
    }
    return action_performed(actions, opt);
}
*/

MENU(main,
    CASE(ID_MAIN_MENU_ROOMS, rooms)
    CASE(ID_MAIN_MENU_BOOKINGS, bookings)
    ,
    MENU(rooms,
        CASE(ID_ROOMS_MENU_VIEW, view_rooms)
        CASE(ID_ROOMS_MENU_ADD, add_room)
        ,
        MENU(view_rooms,
            CASE(ID_VIEW_ROOMS_MENU_ALL_ROOMS, all_rooms)
            CASE(ID_VIEW_ROOMS_MENU_FILTER, filter)
            ,
            MENU(all_rooms,
                // open specific room menu
            )
            MENU(filter,
                CASE(ID_FILTER_MENU_FILTER_NAME, filter_name)
                CASE(ID_FILTER_MENU_FILTER_CAPACITY, filter_capacity)
                CASE(ID_FILTER_MENU_FILTER_AVAILABILITY, filter_availability)
                //CASE(ID_FILTER_MENU_APPLY, apply)
                ,
                MENU(filter_name,
                    // filter name input
                )
                MENU(filter_capacity,
                    // filter capacity input
                )
                MENU(filter_availability,
                    // filter availability input
                )
            )
        )
        MENU(add_room,
        )
    )
    MENU(bookings,
        // open specific booking menu
    )
)

override
void app1_main(app a) {
    _load_rooms();

    MENU_SCREEN(main, main_menu());
}
