// Copyright (C) 2016 David Reid. See included LICENSE file.

#define DRED_CONTROL_TYPE_SCROLLBAR   "dred.common.scrollbar"

typedef struct dred_scrollbar dred_scrollbar;
#define DRED_SCROLLBAR(a) ((dred_scrollbar*)(a))

typedef enum
{
    dred_scrollbar_orientation_none,
    dred_scrollbar_orientation_vertical,
    dred_scrollbar_orientation_horizontal
} dred_scrollbar_orientation;

typedef void (* dred_scrollbar_on_scroll_proc)(dred_scrollbar* pScrollbar, int scrollPos);

struct dred_scrollbar
{
    // The base control.
    dred_control control;


    /// The orientation.
    dred_scrollbar_orientation orientation;

    /// The minimum scroll range.
    int rangeMin;

    /// The maximum scroll range.
    int rangeMax;

    /// The page size.
    int pageSize;

    /// The current scroll position.
    int scrollPos;

    /// Whether or not to auto-hide the thumb.
    dr_bool32 autoHideThumb;

    /// The mouse wheel scale.
    int mouseWheelScale;

    /// The color of the track.
    dred_color trackColor;

    /// The color of the thumb while not hovered or pressed.
    dred_color thumbColor;

    /// The color of the thumb while hovered.
    dred_color thumbColorHovered;

    /// The color of the thumb while pressed.
    dred_color thumbColorPressed;

    /// The function to call when the scroll position changes.
    dred_scrollbar_on_scroll_proc onScroll;


    /// The current size of the thumb.
    float thumbSize;

    /// The current position of the thumb.
    float thumbPos;

    /// The amount of padding between the edge of the scrollbar and the thumb.
    float thumbPadding;

    /// Whether or not we are hovered over the thumb.
    dr_bool32 thumbHovered;

    /// Whether or not the thumb is pressed.
    dr_bool32 thumbPressed;

    /// The relative position of the mouse on the x axis at the time the thumb was pressed with the mouse.
    float thumbClickPosX;

    /// The relative position of the mouse on the y axis at the time the thumb was pressed with the mouse.
    float thumbClickPosY;
};


/// Creates a scrollbar element.
dr_bool32 dred_scrollbar_init(dred_scrollbar* pScrollbar, dred_context* pDred, dred_control* pParent, dred_scrollbar_orientation orientation);

/// Deletes the given scrollbar element.
void dred_scrollbar_uninit(dred_scrollbar* pScrollbar);


/// Retrieves the orientation of the given scrollbar.
dred_scrollbar_orientation dred_scrollbar_get_orientation(dred_scrollbar* pScrollbar);


/// Sets the given scrollbar's range.
void dred_scrollbar_set_range(dred_scrollbar* pScrollbar, int rangeMin, int rangeMax);

/// Retrieves the given scrollbar's range.
void dred_scrollbar_get_range(dred_scrollbar* pScrollbar, int* pRangeMinOut, int* pRangeMaxOut);


/// Sets the page size of the given scrollbar's page.
void dred_scrollbar_set_page_size(dred_scrollbar* pScrollbar, int pageSize);

/// Retrieves the page size of the given scrollbar's page.
int dred_scrollbar_get_page_size(dred_scrollbar* pScrollbar);


/// Sets the range and page size.
///
/// @remarks
///     Use this when both the range and page size need to be updated at the same time.
void dred_scrollbar_set_range_and_page_size(dred_scrollbar* pScrollbar, int rangeMin, int rangeMax, int pageSize);


/// Explicitly sets the scroll position.
///
/// @remarks
///     This will move the thumb, but not post the on_scroll event.
///     @par
///     The scroll position will be clamped to the current range, minus the page size.
void dred_scrollbar_set_scroll_position(dred_scrollbar* pScrollbar, int position);

/// Retrieves the scroll position.
int dred_scrollbar_get_scroll_position(dred_scrollbar* pScrollbar);


/// Scrolls by the given amount.
///
/// @remarks
///     If the resulting scroll position differs from the old one, the on on_scroll event will be posted.
void dred_scrollbar_scroll(dred_scrollbar* pScrollbar, int offset);

/// Scrolls to the given position.
///
/// @remarks
///     This differs from dred_scrollbar_set_scroll_position in that it will post the on_scroll event.
///     @par
///     Note that the actual maximum scrollable position is equal to the maximum range value minus the page size.
void dred_scrollbar_scroll_to(dred_scrollbar* pScrollbar, int newScrollPos);


/// Enables auto-hiding of the thumb.
void dred_scrollbar_enable_thumb_auto_hide(dred_scrollbar* pScrollbar);

/// Disables auto-hiding of the thumb.
void dred_scrollbar_disable_thumb_auto_hide(dred_scrollbar* pScrollbar);

/// Determines whether or not thumb auto-hiding is enabled.
dr_bool32 dred_scrollbar_is_thumb_auto_hide_enabled(dred_scrollbar* pScrollbar);

/// Determines whether or not the thumb is visible.
///
/// @remarks
///     This is determined by whether or not the thumb is set to auto-hide and the current range and page size.
dr_bool32 dred_scrollbar_is_thumb_visible(dred_scrollbar* pScrollbar);


/// Sets the mouse wheel scale.
///
/// @remarks
///     Set this to a negative value to reverse the direction.
void dred_scrollbar_set_mouse_wheel_scele(dred_scrollbar* pScrollbar, int scale);

/// Retrieves the mouse wheel scale.
int dred_scrollbar_get_mouse_wheel_scale(dred_scrollbar* pScrollbar);


/// Sets the color of the track.
void dred_scrollbar_set_track_color(dred_scrollbar* pScrollbar, dred_color color);

/// Sets the default color of the thumb.
void dred_scrollbar_set_default_thumb_color(dred_scrollbar* pScrollbar, dred_color color);

/// Sets the hovered color of the thumb.
void dred_scrollbar_set_hovered_thumb_color(dred_scrollbar* pScrollbar, dred_color color);

/// Sets the pressed color of the thumb.
void dred_scrollbar_set_pressed_thumb_color(dred_scrollbar* pScrollbar, dred_color color);


/// Sets the function to call when the given scrollbar is scrolled.
void dred_scrollbar_set_on_scroll(dred_scrollbar* pScrollbar, dred_scrollbar_on_scroll_proc onScroll);

/// Retrieves the function call when the given scrollbar is scrolled.
dred_scrollbar_on_scroll_proc dred_scrollbar_get_on_scroll(dred_scrollbar* pScrollbar);


/// Calculates the relative rectangle of the given scrollbar's thumb.
dred_rect dred_scrollbar_get_thumb_rect(dred_scrollbar* pScrollbar);


/// Called when the size event needs to be processed for the given scrollbar.
void dred_scrollbar_on_size(dred_control* pControl, float newWidth, float newHeight);

/// Called when the mouse leave event needs to be processed for the given scrollbar.
void dred_scrollbar_on_mouse_leave(dred_control* pControl);

/// Called when the mouse move event needs to be processed for the given scrollbar.
void dred_scrollbar_on_mouse_move(dred_control* pControl, int relativeMousePosX, int relativeMousePosY, int stateFlags);

/// Called when the mouse button down event needs to be processed for the given scrollbar.
void dred_scrollbar_on_mouse_button_down(dred_control* pControl, int button, int relativeMousePosX, int relativeMousePosY, int stateFlags);

/// Called when the mouse button up event needs to be processed for the given scrollbar.
void dred_scrollbar_on_mouse_button_up(dred_control* pControl, int button, int relativeMousePosX, int relativeMousePosY, int stateFlags);

/// Called when the mouse wheel event needs to be processed for the given scrollbar.
void dred_scrollbar_on_mouse_wheel(dred_control* pControl, int delta, int relativeMousePosX, int relativeMousePosY, int stateFlags);

/// Called when the paint event needs to be processed.
void dred_scrollbar_on_paint(dred_control* pControl, dred_rect relativeClippingRect, void* pPaintData);
