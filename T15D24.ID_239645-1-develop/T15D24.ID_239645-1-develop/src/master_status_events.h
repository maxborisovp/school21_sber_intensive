#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

typedef struct {
    int event_id;
    int module_id;
    int new_module_status;
    char status_change_date[11];
    char status_change_time[9];
} Status_event;

#endif
