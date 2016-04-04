#include "GrabAndThrow.h"

void GrabAndThrow::PressButtons()
{
    //Do the grab if we're in a state to do so and haven't yet
    if(m_state->m_memory->player_two_action != GRAB &&
        m_state->m_memory->player_two_action != GRAB_RUNNING &&
        m_state->m_memory->player_two_action != THROW_FORWARD &&
        m_state->m_memory->player_two_action != THROW_BACK &&
        m_state->m_memory->player_two_action != THROW_UP &&
        m_state->m_memory->player_two_action != THROW_DOWN &&
        m_state->m_memory->player_two_action != GRAB_PULLING &&
        m_state->m_memory->player_two_action != GRAB_WAIT)
    {
        m_controller->pressButton(Controller::BUTTON_Z);
        return;
    }

    if(m_state->m_memory->player_two_action == GRAB_PULLING)
    {
        m_controller->emptyInput();
        return;
    }

    //Perform a throw
    if(m_state->m_memory->player_two_action == GRAB_WAIT)
    {
        switch(m_direction)
        {
            case UP_THROW:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 1);
                break;
            }
            case DOWN_THROW:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                break;
            }
            case BACK_THROW:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, m_state->m_memory->player_two_facing ? 0 : 1, .5);
                break;
            }
            case FORWARD_THROW:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, m_state->m_memory->player_two_facing ? 1 : 0, .5);
                break;
            }
        }
        return;
    }

    //If we get the throw, then let go for a frame
    if(m_state->m_memory->player_two_action == THROW_UP ||
        m_state->m_memory->player_two_action == THROW_DOWN ||
        m_state->m_memory->player_two_action == THROW_BACK ||
        m_state->m_memory->player_two_action == THROW_FORWARD)
    {
        m_controller->emptyInput();
        return;
    }

    //If we miss the grab, let go for a frame
    if((m_state->m_memory->player_two_action == GRAB ||
        m_state->m_memory->player_two_action == GRAB_RUNNING) &&
        m_state->m_memory->player_two_action_frame > 15)
    {
        m_controller->emptyInput();
        return;
    }
}

bool GrabAndThrow::IsInterruptible()
{
    if((m_state->m_memory->player_two_action == GRAB ||
        m_state->m_memory->player_two_action == GRAB_RUNNING) &&
        m_state->m_memory->player_two_action_frame > 20)
    {
        return true;
    }

    if(m_state->m_memory->player_two_action == THROW_UP ||
        m_state->m_memory->player_two_action == THROW_DOWN ||
        m_state->m_memory->player_two_action == THROW_BACK ||
        m_state->m_memory->player_two_action == THROW_FORWARD)
    {
        return true;
    }

    //Safety return
    uint frame = m_state->m_memory->frame - m_startingFrame;
    if(frame >= 120)
    {
        return true;
    }
    return false;}

GrabAndThrow::GrabAndThrow(THROW_DIRECTION direction)
{
    m_direction = direction;
}

GrabAndThrow::~GrabAndThrow()
{
}
