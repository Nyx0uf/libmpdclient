/* libmpdclient
   (c) 2003-2009 The Music Player Daemon Project
   This project's homepage is: http://www.musicpd.org

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <mpd/player.h>
#include <mpd/send.h>
#include <mpd/song.h>
#include <mpd/response.h>
#include "isend.h"
#include "run.h"

#include <limits.h>
#include <stdio.h>

bool
mpd_send_currentsong(struct mpd_connection *connection)
{
	return mpd_send_command(connection, "currentsong", NULL);
}

struct mpd_song *
mpd_run_currentsong(struct mpd_connection *connection)
{
	struct mpd_song *song;

	if (!mpd_run_check(connection) || !mpd_send_currentsong(connection))
		return NULL;

	song = mpd_recv_song(connection);
	if (song == NULL)
		return NULL;

	if (!mpd_response_finish(connection)) {
		mpd_song_free(song);
		return NULL;
	}

	return song;
}

bool
mpd_send_play(struct mpd_connection *connection)
{
	return mpd_send_command(connection, "play", NULL);
}

bool
mpd_run_play(struct mpd_connection *connection)
{
	return mpd_run_check(connection) && mpd_send_play(connection) &&
		mpd_response_finish(connection);
}

bool
mpd_send_playpos(struct mpd_connection *connection, unsigned song_pos)
{
	return mpd_send_int_command(connection, "play", song_pos);
}

bool
mpd_run_playpos(struct mpd_connection *connection, unsigned song_pos)
{
	return mpd_run_check(connection) &&
		mpd_send_playpos(connection, song_pos) &&
		mpd_response_finish(connection);
}

bool
mpd_send_playid(struct mpd_connection *connection, unsigned id)
{
	return mpd_send_int_command(connection, "playid", id);
}

bool
mpd_run_playid(struct mpd_connection *connection, unsigned song_id)
{
	return mpd_run_check(connection) &&
		mpd_send_playid(connection, song_id) &&
		mpd_response_finish(connection);
}

bool
mpd_send_stop(struct mpd_connection *connection)
{
	return mpd_send_command(connection, "stop", NULL);
}

bool
mpd_run_stop(struct mpd_connection *connection)
{
	return mpd_run_check(connection) && mpd_send_stop(connection) &&
		mpd_response_finish(connection);
}

bool
mpd_send_toggle_pause(struct mpd_connection *connection)
{
	return mpd_send_command(connection, "pause", NULL);
}

bool
mpd_run_toggle_pause(struct mpd_connection *connection)
{
	return mpd_run_check(connection) &&
		mpd_send_toggle_pause(connection) &&
		mpd_response_finish(connection);
}

bool
mpd_send_pause(struct mpd_connection *connection, bool mode)
{
	return mpd_send_int_command(connection, "pause", mode);
}

bool
mpd_run_pause(struct mpd_connection *connection, bool mode)
{
	return mpd_run_check(connection) && mpd_send_pause(connection, mode) &&
		mpd_response_finish(connection);
}

bool
mpd_send_next(struct mpd_connection *connection)
{
	return mpd_send_command(connection, "next", NULL);
}

bool
mpd_run_next(struct mpd_connection *connection)
{
	return mpd_run_check(connection) && mpd_send_next(connection) &&
		mpd_response_finish(connection);
}

bool
mpd_send_previous(struct mpd_connection *connection)
{
	return mpd_send_command(connection, "previous", NULL);
}

bool
mpd_run_previous(struct mpd_connection *connection)
{
	return mpd_run_check(connection) && mpd_send_previous(connection) &&
		mpd_response_finish(connection);
}

bool
mpd_send_seek(struct mpd_connection *connection, unsigned t)
{
	return mpd_send_int2_command(connection, "seek", -1, t);
}

bool
mpd_run_seek(struct mpd_connection *connection, unsigned t)
{
	return mpd_run_check(connection) && mpd_send_seek(connection, t) &&
		mpd_response_finish(connection);
}

bool
mpd_send_seekpos(struct mpd_connection *connection,
		 unsigned song_pos, unsigned t)
{
	return mpd_send_int2_command(connection, "seek", song_pos, t);
}

bool
mpd_run_seekpos(struct mpd_connection *connection,
		unsigned song_pos, unsigned t)
{
	return mpd_run_check(connection) &&
		mpd_send_seekpos(connection, song_pos, t) &&
		mpd_response_finish(connection);
}

bool
mpd_send_seekid(struct mpd_connection *connection, unsigned id, unsigned t)
{
	return mpd_send_int2_command(connection, "seekid", id, t);
}

bool
mpd_run_seekid(struct mpd_connection *connection,
	       unsigned song_id, unsigned t)
{
	return mpd_run_check(connection) &&
		mpd_send_seekid(connection, song_id, t) &&
		mpd_response_finish(connection);
}

bool
mpd_send_repeat(struct mpd_connection *connection, bool mode)
{
	return mpd_send_int_command(connection, "repeat", mode);
}

bool
mpd_run_repeat(struct mpd_connection *connection, bool mode)
{
	return mpd_run_check(connection) &&
		mpd_send_repeat(connection, mode) &&
		mpd_response_finish(connection);
}

bool
mpd_send_random(struct mpd_connection *connection, bool mode)
{
	return mpd_send_int_command(connection, "random", mode);
}

bool
mpd_run_random(struct mpd_connection *connection, bool mode)
{
	return mpd_run_check(connection) &&
		mpd_send_random(connection, mode) &&
		mpd_response_finish(connection);
}

bool
mpd_send_single(struct mpd_connection *connection, bool mode)
{
	return mpd_send_int_command(connection, "single", mode);
}

bool
mpd_run_single(struct mpd_connection *connection, bool mode)
{
	return mpd_run_check(connection) &&
		mpd_send_single(connection, mode) &&
		mpd_response_finish(connection);
}

bool
mpd_send_consume(struct mpd_connection *connection, bool mode)
{
	return mpd_send_int_command(connection, "consume", mode);
}

bool
mpd_run_consume(struct mpd_connection *connection, bool mode)
{
	return mpd_run_check(connection) &&
		mpd_send_consume(connection, mode) &&
		mpd_response_finish(connection);
}

bool
mpd_send_crossfade(struct mpd_connection *connection, unsigned seconds)
{
	return mpd_send_int_command(connection, "crossfade", seconds);
}

bool
mpd_run_crossfade(struct mpd_connection *connection, unsigned seconds)
{
	return mpd_run_check(connection) &&
		mpd_send_crossfade(connection, seconds) &&
		mpd_response_finish(connection);
}
