#include "model/model_view.h"
#include "utils/terminal.h"

void quit_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)model, (void)data, (void)row;

    state->exited = true;
}

void help_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    terminal_clear();

    for (int i = 0; model.get_actions()[i].key_codepoint != 0; i++)
    {
        ModelAction action = model.get_actions()[i];

        printf("\n\t • [%c] %s - %s ", action.key_codepoint, action.name, action.desciption);
    }

    terminal_read_key();
}

void scroll_up_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)model, (void)data, (void)row;

    state->slected--;
}

void scroll_down_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    state->slected++;
}

void page_up_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    state->slected -= 10;
}

void page_down_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    state->slected += 10;
}

void home_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    state->slected = 0;
}

void end_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    state->slected = model.row_count(data);
}

void edit_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    //model_view_edit(*state, model, data, row);
    state->sort_dirty = true;
}

void create_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    int new_row = model.row_create(data);
    edit_ModelActionCallback(surface, state, model, data, new_row);
    state->sort_dirty = true;
}

void delete_ModelActionCallback(Surface *surface, ModelViewState *state, Model model, void *data, int row)
{
    (void)surface, (void)state, (void)model, (void)data, (void)row;

    model.row_delete(data, state->sorted[state->slected]);
    state->sort_dirty = true;
}