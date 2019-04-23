/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:31:18 by bturcott          #+#    #+#             */
/*   Updated: 2019/04/23 15:15:49 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define OPEN_MAP "./sounds/map.wav"
#define ENCOUNTER_WALLS "./sounds/collision.wav"
#define STEPS "./sounds/steps.wav"
#define CUSTOM "./sounds/custom.wav"
#define MUSIC "./sounds/music.wav"

int init_music(t_sdl *sdl)
{
    Mix_Music **samples;
    if ((Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1))
    {
        ft_putendl("no music :(");
        return (-1);
    }
    if (!(samples = ft_memalloc(sizeof(Mix_Music *) * 5)))
        return(-1);
    samples[0] = Mix_LoadMUS(MUSIC);
    samples[1] = Mix_LoadMUS(OPEN_MAP);
    samples[2] = Mix_LoadMUS(STEPS);
    samples[3] = Mix_LoadMUS(ENCOUNTER_WALLS);
    samples[4] = Mix_LoadMUS(CUSTOM);
    if (Mix_PlayMusic(samples[0], -1) == -1)
        ft_putendl("no music :(");
    return (1);
}

int music_control_panel(Mix_Music **samples, int command)
{
    if (command == 1)
        Mix_PlayMusic(samples[1], 1);
    else if (command == 2)
        Mix_PlayMusic(samples[2], 1);
    else if (command == 3)
        Mix_PlayMusic(samples[3], 1);
    else if (command == 4)
        Mix_PlayMusic(samples[4], 1);
    else if (command == 5)
        Mix_PlayMusic(samples[0], 0);
    else if (command == 6)
        Mix_PlayMusic(samples[0], -1);
    return (0);
}
