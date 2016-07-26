// Copyright (C) 2016 David Reid. See included LICENSE file.

#define DRED_CONTROL_TYPE_TEXTBOX  "dred.textbox"

typedef struct dred_textbox dred_textbox;
#define DRED_TEXTBOX(a) ((dred_textbox*)(a))

typedef void (* dred_textbox_on_cursor_move_proc)(dred_textbox* pTextBox);
typedef void (* dred_textbox_on_undo_point_changed_proc)(dred_textbox* pTextBox, unsigned int iUndoPoint);

// A cursor in a textbox is tied to either 1 or 0 selection regions. When a cursor is not associated with a selection, the
// index of the selection region is set to -1.
typedef struct
{
    size_t iEngineCursor;        // <-- Always >= 0.
    size_t iEngineSelection;     // <-- Set to -1 if the cursor is not associated with a selection.
} dred_textbox_cursor;

struct dred_textbox
{
    // The base control.
    dred_control control;


    /// The text engine.
    drte_engine textEngine;
    drte_engine* pTL;

    // The default style for use by the text engine.
    dred_text_style defaultStyle;

    // The style to apply to selected text. Only the background color is used.
    dred_text_style selectionStyle;

    // The style to apply to active lines.
    dred_text_style activeLineStyle;

    // The style to apply to the cursor.
    dred_text_style cursorStyle;

    // The style to apply to line numbers.
    dred_text_style lineNumbersStyle;


    /// The vertical scrollbar.
    dred_scrollbar vertScrollbar;
    dred_scrollbar* pVertScrollbar;

    /// The horizontal scrollbar.
    dred_scrollbar horzScrollbar;
    dred_scrollbar* pHorzScrollbar;

    /// The line numbers element.
    dred_control lineNumbers;
    dred_control* pLineNumbers; // <-- Always equal to &lineNumbers and only used for convenience.


    /// The color of the border.
    dred_color borderColor;

    /// The width of the border.
    float borderWidth;

    /// The amount of padding to apply the left and right of the text.
    float padding;

    // The width of the line numbers.
    float lineNumbersWidth;

    /// The padding to the right of the line numbers.
    float lineNumbersPaddingRight;


    /// The desired width of the vertical scrollbar.
    float vertScrollbarSize;

    /// The desired height of the horizontal scrollbar.
    float horzScrollbarSize;

    /// Whether or not the vertical scrollbar is enabled.
    bool isVertScrollbarEnabled;

    /// Whether or not the horizontal scrollbar is enabled.
    bool isHorzScrollbarEnabled;

    // Whether or not an extra page is added to the scroll range so that the user can scroll past the last line. When set to true,
    // the user can scroll until the last line is sitting at the top of the text box. When disabled the user can scroll until the
    // last line is sitting at the bottom.
    bool isExcessScrollingEnabled;

    // Whether or not tabs to spaces is enabled.
    bool isTabsToSpacesEnabled;


    // The number of active cursors.
    size_t cursorCount;

    // The buffer containing the active cursors.
    dred_textbox_cursor* pCursors;


    /// When selecting lines by clicking and dragging on the line numbers, keeps track of the line to anchor the selection to.
    size_t iLineSelectAnchor;


    // Whether or not we are doing word based mouse-drag selection.
    bool isDoingWordSelect;

    // The word to act as the achor when doing word based selection.
    drte_region wordSelectionAnchor;


    /// The function to call when the text cursor/caret moves.
    dred_textbox_on_cursor_move_proc onCursorMove;

    /// The function to call when the undo point changes.
    dred_textbox_on_undo_point_changed_proc onUndoPointChanged;


    // The timer for stepping the cursor.
    dred_timer* pTimer;
};


// Creates a new text box control.
bool dred_textbox_init(dred_textbox* pTextBox, dred_context* pDred, dred_control* pParent);

// Deletes the given text box control.
void dred_textbox_uninit(dred_textbox* pTextBox);


// Retrieves a pointer to the internal text engine.
drte_engine* dred_textbox_get_engine(dred_textbox* pTextBox);


// Sets the font to use with the given text box.
void dred_textbox_set_font(dred_textbox* pTextBox, dred_gui_font* pFont);

// Retrieves the font being used with the given text box.
dred_gui_font* dred_textbox_get_font(dred_textbox* pTextBox);

// Sets the color of the text in teh given text box.
void dred_textbox_set_text_color(dred_textbox* pTextBox, dred_color color);

// Sets the background color of the given text box.
void dred_textbox_set_background_color(dred_textbox* pTextBox, dred_color color);

// Sets the background color of selected text.
void dred_textbox_set_selection_background_color(dred_textbox* pTextBox, dred_color color);

// Retrieves the background color of selected text.
dred_color dred_textbox_get_selection_background_color(dred_textbox* pTextBox);

// Sets the background color for the line the caret is currently sitting on.
void dred_textbox_set_active_line_background_color(dred_textbox* pTextBox, dred_color color);

// Sets the width of the text cursor.
void dred_textbox_set_cursor_width(dred_textbox* pTextBox, float cursorWidth);

// Retrieves the width of the text cursor.
float dred_textbox_get_cursor_width(dred_textbox* pTextBox);

// Sets the color of the cursor of the given text box.
void dred_textbox_set_cursor_color(dred_textbox* pTextBox, dred_color color);

// Sets the border color of the given text box.
void dred_textbox_set_border_color(dred_textbox* pTextBox, dred_color color);

// Sets the border width of the given text box.
void dred_textbox_set_border_width(dred_textbox* pTextBox, float borderWidth);

// Sets the amount of padding to apply to given text box.
void dred_textbox_set_padding(dred_textbox* pTextBox, float padding);

// Retrieves the amound of vertical padding to apply to the given text box.
float dred_textbox_get_padding_vert(dred_textbox* pTextBox);

// Retrieves the amound of horizontal padding to apply to the given text box.
float dred_textbox_get_padding_horz(dred_textbox* pTextBox);

// Sets the width of the line numbers.
void dred_textbox_set_line_numbers_width(dred_textbox* pTextBox, float lineNumbersWidth);

// Retrieves the width of the line numbers.
float dred_textbox_get_line_numbers_width(dred_textbox* pTextBox);

// Sets the padding to apply between the line numbers and the text.
void dred_textbox_set_line_numbers_padding(dred_textbox* pTextBox, float lineNumbersPadding);

// Retrieves the padding to apply between the line numbers and the text.
float dred_textbox_get_line_numbers_padding(dred_textbox* pTextBox);

// Sets the color of the text of the line numbers.
void dred_textbox_set_line_numbers_color(dred_textbox* pTextBox, dred_color color);

// Retrieves the color of the text of the line numbers.
dred_color dred_textbox_get_line_numbers_color(dred_textbox* pTextBox);

// Sets the color of the background of the line numbers.
void dred_textbox_set_line_numbers_background_color(dred_textbox* pTextBox, dred_color color);

// Retrieves the color of the background of the line numbers.
dred_color dred_textbox_get_line_numbers_background_color(dred_textbox* pTextBox);

// Sets the color of the track of the scrollbars.
void dred_textbox_set_scrollbar_track_color(dred_textbox* pTextBox, dred_color color);

// Sets the color of the thumb of the scrollbars.
void dred_textbox_set_scrollbar_thumb_color(dred_textbox* pTextBox, dred_color color);

// Sets the color of the thumb of the scrollbars while hovered.
void dred_textbox_set_scrollbar_thumb_color_hovered(dred_textbox* pTextBox, dred_color color);

// Sets the color of the thumb of the scrollbars while pressed.
void dred_textbox_set_scrollbar_thumb_color_pressed(dred_textbox* pTextBox, dred_color color);


// Enables word wrap.
void dred_textbox_enable_word_wrap(dred_textbox* pTextBox);

// Disables word wrap.
void dred_textbox_disable_word_wrap(dred_textbox* pTextBox);

// Determines whether or not word wrap is enabled.
bool dred_textbox_is_word_wrap_enabled(dred_textbox* pTextBox);


// Sets the text of the given text box.
void dred_textbox_set_text(dred_textbox* pTextBox, const char* text);

// Retrieves the text of the given text box.
size_t dred_textbox_get_text(dred_textbox* pTextBox, char* pTextOut, size_t textOutSize);

// Steps the text box to allow it to blink the cursor.
void dred_textbox_step(dred_textbox* pTextBox, unsigned int milliseconds);

// Sets the blink rate of the cursor in milliseconds.
void dred_textbox_set_cursor_blink_rate(dred_textbox* pTextBox, unsigned int blinkRateInMilliseconds);

// Moves the caret to the end of the text.
void dred_textbox_move_cursor_to_end_of_text(dred_textbox* pTextBox);

// Moves the caret to the beginning of the line at the given index.
void dred_textbox_move_cursor_to_start_of_line_by_index(dred_textbox* pTextBox, size_t iLine);

// Determines whether or not anything is selected in the given text box.
bool dred_textbox_is_anything_selected(dred_textbox* pTextBox);

// Selects all of the text inside the text box.
void dred_textbox_select_all(dred_textbox* pTextBox);

// Deselect everything.
void dred_textbox_deselect_all(dred_textbox* pTextBox);

// Retrieves a copy of the selected text.
//
// @remarks
//     This returns the length of the selected text. Call this once with <textOut> set to NULL to calculate the required size of the
//     buffer.
//     @par
//     If the output buffer is not larger enough, the string will be truncated.
size_t dred_textbox_get_selected_text(dred_textbox* pTextBox, char* textOut, size_t textOutLength);

// Deletes the character to the right of the cursor.
//
// @return True if the text within the text engine has changed.
bool dred_textbox_delete_character_to_right_of_cursor(dred_textbox* pTextBox);

// Deletes the currently selected text.
//
// @return True if the text within the text engine has changed.
bool dred_textbox_delete_selected_text_no_undo(dred_textbox* pTextBox);
bool dred_textbox_delete_selected_text(dred_textbox* pTextBox);

// Inserts a character at the position of the cursor.
//
// @return True if the text within the text engine has changed.
bool dred_textbox_insert_text_at_cursors_no_undo(dred_textbox* pTextBox, const char* text);
bool dred_textbox_insert_text_at_cursors(dred_textbox* pTextBox, const char* text);

// Unindents selected text.
bool dred_textbox_unindent_selected_blocks(dred_textbox* pTextBox);

// Performs an undo operation.
bool dred_textbox_undo(dred_textbox* pTextBox);

// Performs a redo operation.
bool dred_textbox_redo(dred_textbox* pTextBox);

// Retrieves the number of undo points remaining.
unsigned int dred_textbox_get_undo_points_remaining_count(dred_textbox* pTextBox);

// Retrieves the number of redo points remaining.
unsigned int dred_textbox_get_redo_points_remaining_count(dred_textbox* pTextBox);

// Clears the undo/redo stack.
void dred_textbox_clear_undo_stack(dred_textbox* pTextBox);

// Retrieves the index of the line the cursor is current sitting on.
size_t dred_textbox_get_cursor_line(dred_textbox* pTextBox);

// Retrieves the index of the column the cursor is current sitting on.
size_t dred_textbox_get_cursor_column(dred_textbox* pTextBox);

// Retrieves the number of lines in the given text box.
size_t dred_textbox_get_line_count(dred_textbox* pTextBox);


// Finds and selects the next occurance of the given string, starting from the cursor and looping back to the start.
bool dred_textbox_find_and_select_next(dred_textbox* pTextBox, const char* text);

// Finds the next occurance of the given string and replaces it with another.
bool dred_textbox_find_and_replace_next(dred_textbox* pTextBox, const char* text, const char* replacement);

// Finds every occurance of the given string and replaces it with another.
bool dred_textbox_find_and_replace_all(dred_textbox* pTextBox, const char* text, const char* replacement);


// Shows the line numbers.
void dred_textbox_show_line_numbers(dred_textbox* pTextBox);

// Hides the line numbers.
void dred_textbox_hide_line_numbers(dred_textbox* pTextBox);


// Disables the vertical scrollbar.
void dred_textbox_disable_vertical_scrollbar(dred_textbox* pTextBox);

// Enables the vertical scrollbar.
void dred_textbox_enable_vertical_scrollbar(dred_textbox* pTextBox);

// Disables the horizontal scrollbar.
void dred_textbox_disable_horizontal_scrollbar(dred_textbox* pTextBox);

// Enables the horizontal scrollbar.
void dred_textbox_enable_horizontal_scrollbar(dred_textbox* pTextBox);

// Retrieves the vertical scrollbar.
dred_scrollbar* dred_textbox_get_vertical_scrollbar(dred_textbox* pTextBox);

// Retrieves the horizontal scrollbar.
dred_scrollbar* dred_textbox_get_horizontal_scrollbar(dred_textbox* pTextBox);

// Sets the size of both the vertical and horizontal scrollbars.
void dred_textbox_set_scrollbar_size(dred_textbox* pTextBox, float size);

// Enables excess scrolling on the vertical scrollbar.
void dred_textbox_enable_excess_scrolling(dred_textbox* pTextBox);

// Disables excess scrolling on the vertical scrollbar.
void dred_textbox_disable_excess_scrolling(dred_textbox* pTextBox);


// Sets the size of tabs in spaces.
void dred_textbox_set_tab_size_in_spaces(dred_textbox* pTextBox, unsigned int tabSizeInSpaces);

// Retrieves the size of tabs in spaces.
unsigned int dred_textbox_get_tab_size_in_spaces(dred_textbox* pTextBox);

// Enables tabs-to-spaces.
void dred_textbox_enable_tabs_to_spaces(dred_textbox* pTextBox);

// Disables tab-to-spaces.
void dred_textbox_disable_tabs_to_spaces(dred_textbox* pTextBox);

// Determines whether or not the textbox should convert tabs to spaces.
bool dred_textbox_is_tabs_to_spaces_enabled(dred_textbox* pTextBox);


// Prepares an undo point.
bool dred_textbox_prepare_undo_point(dred_textbox* pTextBox);

// Commits an undo point.
bool dred_textbox_commit_undo_point(dred_textbox* pTextBox);


// Sets the function to call when the cursor moves.
void dred_textbox_set_on_cursor_move(dred_textbox* pTextBox, dred_textbox_on_cursor_move_proc proc);

// Sets the function to call when the undo point changes.
void dred_textbox_set_on_undo_point_changed(dred_textbox* pTextBox, dred_textbox_on_undo_point_changed_proc proc);



// on_size.
void dred_textbox_on_size(dred_control* pControl, float newWidth, float newHeight);

// on_mouse_move.
void dred_textbox_on_mouse_move(dred_control* pControl, int relativeMousePosX, int relativeMousePosY, int stateFlags);

// on_mouse_button_down.
void dred_textbox_on_mouse_button_down(dred_control* pControl, int mouseButton, int relativeMousePosX, int relativeMousePosY, int stateFlags);

// on_mouse_button_up.
void dred_textbox_on_mouse_button_up(dred_control* pControl, int mouseButton, int relativeMousePosX, int relativeMousePosY, int stateFlags);

// on_mouse_button_dblclick.
void dred_textbox_on_mouse_button_dblclick(dred_control* pControl, int mouseButton, int relativeMousePosX, int relativeMousePosY, int stateFlags);

// on_mouse_wheel
void dred_textbox_on_mouse_wheel(dred_control* pControl, int delta, int relativeMousePosX, int relativeMousePosY, int stateFlags);

// on_key_down.
void dred_textbox_on_key_down(dred_control* pControl, dred_key key, int stateFlags);

// on_key_up.
void dred_textbox_on_key_up(dred_control* pControl, dred_key key, int stateFlags);

// on_printable_key_down.
void dred_textbox_on_printable_key_down(dred_control* pControl, unsigned int utf32, int stateFlags);

// on_paint.
void dred_textbox_on_paint(dred_control* pControl, dred_rect relativeRect, void* pPaintData);

// on_capture_keyboard
void dred_textbox_on_capture_keyboard(dred_control* pControl, dred_control* pPrevCapturedControl);

// on_release_keyboard
void dred_textbox_on_release_keyboard(dred_control* pControl, dred_control* pNewCapturedControl);

// on_capture_mouse
void dred_textbox_on_capture_mouse(dred_control* pControl);

// on_release_mouse
void dred_textbox_on_release_mouse(dred_control* pControl);
