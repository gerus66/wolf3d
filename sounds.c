/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:31:18 by bturcott          #+#    #+#             */
/*   Updated: 2019/04/25 10:51:54 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define OPEN_MAP "./sounds/map.wav"
#define ENCOUNTER_WALLS "./sounds/collision.wav"
#define STEPS "./sounds/steps.wav"
#define CUSTOM "./sounds/custom.wav"
#define MUSIC "./sounds/music.wav"

int		init_music(t_sdl *sdl)
{
	Mix_Chunk **samples;
	Mix_Music *mus;

	if ((Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1))
	{
		ft_putendl("no music :(");
		return (-1);
	}
	if (!(samples = ft_memalloc(sizeof(Mix_Chunk *) * 5)))
		return (-1);
	mus = Mix_LoadMUS(MUSIC);
	samples[0] = Mix_LoadWAV(OPEN_MAP);
	samples[1] = Mix_LoadWAV(STEPS);
	samples[2] = Mix_LoadWAV(ENCOUNTER_WALLS);
	samples[3] = Mix_LoadWAV(CUSTOM);
	sdl->samples = samples;
	sdl->music = mus;
	Mix_PlayMusic(mus, -1);
	Mix_AllocateChannels(4);
	return (1);
}

int		sounds_control_panel(Mix_Chunk **samples, int command)
{
	if (command == 1)
	{
		if (!Mix_Playing(1))
			Mix_PlayChannel(1, samples[0], 0);
	}
	else if (command == 2)
	{
		if (!Mix_Playing(2))
			Mix_PlayChannel(2, samples[1], 0);
	}
	else if (command == 3)
	{
		if (!Mix_Playing(3))
			Mix_PlayChannel(3, samples[2], 0);
	}
	else if (command == 4)
	{
		if (!Mix_Playing(4))
			Mix_PlayChannel(4, samples[3], 0);
	}
	return (0);
}

void	sounds(t_sdl *sdl, SDL_Event e)
{
	SDL_Scancode key;

	key = e.key.keysym.scancode;
	if (key == 26 || key == 4 || key == 22 || key == 7)
		sounds_control_panel(sdl->samples, 2);
	else if (key == 16)
		sounds_control_panel(sdl->samples, 1);
	else if (key == 48)
	{
		if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
}
