#include "SmashAttack.h"

void SmashAttack::PressButtons()
{
    //Jump-cancel the smash
    if(m_state->m_memory->player_two_action == RUNNING ||
        m_state->m_memory->player_two_action == DASHING)
    {
        m_controller->pressButton(Controller::BUTTON_Y);
        return;
    }

    uint frame = m_state->m_memory->frame - m_startingFrame;
    //TODO The charge point changes for different smashes
    if(frame == 1 || frame == 2)
    {
        m_controller->releaseButton(Controller::BUTTON_Y);
        switch(m_direction)
        {
            case LEFT:
            {
                m_controller->pressButton(Controller::BUTTON_A);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 0, .5);
                break;
            }
            case RIGHT:
            {
                m_controller->pressButton(Controller::BUTTON_A);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, .5);
                break;
            }
            case UP:
            {
                m_controller->pressButton(Controller::BUTTON_A);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 1);
                break;
            }
            case DOWN:
            {
                m_controller->pressButton(Controller::BUTTON_A);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                break;
            }
        }
        return;
    }

    //Charge the attack...
    if(m_charge_frames > 0)
    {
        m_charge_frames--;
        //Just keep previous input
        return;
    }
    else
    {
        m_controller->releaseButton(Controller::BUTTON_A);
        m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
    }
}

bool SmashAttack::IsInterruptible()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    if(frame >= 90)
    {
        return true;
    }
    return false;}

SmashAttack::SmashAttack(DIRECTION d, uint charge_frames)
{
    m_direction = d;
    //TODO: Work on transitions to this chain
    m_startingFrame = m_state->m_memory->frame;
    m_charge_frames = charge_frames;
}

SmashAttack::~SmashAttack()
{
}