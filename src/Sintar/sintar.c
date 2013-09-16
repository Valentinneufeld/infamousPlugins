//Spencer Jackson
//sintar.c
#include<sintar.h>
#include<constants.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define MIDDLEC     60
#define MIDDLEF     65
#define MIDDLEG     67
#define MIDDLEB     71
#define LOWESTNOTE  36

//main functions
LV2_Handle init_sintar(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    SINTAR* synth = malloc(sizeof(SINTAR));
    unsigned char i;

    synth->sample_rate = sample_rate;

    init_bridge(&synth->bridge,sample_rate);

    //many many strings
    init_string(&synth->main[0],&synth->bridge,.88, .0003,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEF-12-69)/12),sample_rate,.1);//fourth
   /* init_string(&synth->main[1],&synth->bridge,.88, .0004,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC-12-69)/12),sample_rate,.1);
    init_string(&synth->main[2],&synth->bridge,.88,.00055,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEG-24-69)/12),sample_rate,.1);//down to 5th
    init_string(&synth->main[3],&synth->bridge,.88,.00085,2*PI*(440/sample_rate)*powf(2,(float)(LOWESTNOTE-69)/12),sample_rate,.1);//down octave

    init_string(&synth->drone[0],&synth->bridge,.88,.00027,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEG-12-69)/12),sample_rate,.1);//up 5th
    init_string(&synth->drone[1],&synth->bridge,.88,.00022,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC   -69)/12),sample_rate,.1);//up octave
    init_string(&synth->drone[2],&synth->bridge,.88,.00022,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC+12-69)/12),sample_rate,.1);//up 2 octaves

    init_string(&synth->sympathetic[0], &synth->bridge,.550,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC   -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[1], &synth->bridge,.531,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEB   -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[2], &synth->bridge,.510,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC   -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[3], &synth->bridge,.488,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC+2 -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[4], &synth->bridge,.465,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC+4 -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[5], &synth->bridge,.440,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEF   -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[6], &synth->bridge,.414,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEG   -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[7], &synth->bridge,.386,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEG+2 -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[8], &synth->bridge,.357,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEB   -69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[9], &synth->bridge,.326,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC+12-69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[10],&synth->bridge,.293,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC+14-69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[11],&synth->bridge,.258,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEC+16-69)/12),sample_rate,.1);
    init_string(&synth->sympathetic[12],&synth->bridge,.221,.00013,2*PI*(440/sample_rate)*powf(2,(float)(MIDDLEF+12-69)/12),sample_rate,.1);*/


    synth->nframessince = 0;
/*
    synth->midi_in_p = NULL;
    synth->nactive = 0;
    synth->nsustained = 0;
    synth->pitchbend = 1;
    synth->ibpm = .5;//60/120
    for(i=0;i<127;i++)
    {
        init_note(&(synth->note[i]),
                  &(synth->waves),
                  sample_rate,
                  i,
                  &(synth->ncells),
                  &(synth->cell_lifetime),
                  &(synth->amod_g),
                  &(synth->fmod_g));
        synth->active[i] = 0;
        synth->sustained[i] = 0;
    }

    synth->harmonic_mode = HARMONIC_MODE_SINC;
    for(i=0;i<MAX_N_HARMONICS;i++)
    {
        synth->harm_gain_sinc[i] = 1/(float)(MAX_N_HARMONICS +1);//(nharmonics+1);
        synth->harm_gain_saw[i] = .29/(float)(i+2);//.29 makes it so gain=1 if all harmonics play
        synth->harm_gain_sqr[i] = (i%2!=0)*.48/(float)(i+2);//odd harmonics
        synth->harm_gain_tri[i] = (i%2!=0)*.83/(float)((i+2)*(i+2));
    }
    //fundamental
    synth->harm_gain_sinc[i] = 1/(float)(MAX_N_HARMONICS +1);//(nharmonics+1);
    synth->harm_gain_saw[i] = .29;//.29 makes it so gain=1 if all harmonics play
    synth->harm_gain_sqr[i] = .48;
    synth->harm_gain_tri[i] = .83;

    synth->harm_gains = synth->harm_gain_sinc;

    //get urid map value for midi events
    for (int i = 0; host_features[i]; i++)
    {
        if (strcmp(host_features[i]->URI, LV2_URID__map) == 0)
        {
            LV2_URID_Map *urid_map = (LV2_URID_Map *) host_features[i]->data;
            if (urid_map)
            {
                synth->midi_event_type = urid_map->map(urid_map->handle, LV2_MIDI__MidiEvent);
                synth->other_type = urid_map->map(urid_map->handle, LV2_ATOM__Blank);
                synth->long_type = urid_map->map(urid_map->handle, LV2_ATOM__Long);
                synth->float_type = urid_map->map(urid_map->handle, LV2_ATOM__Float);
                synth->time_info_type = urid_map->map(urid_map->handle, LV2_TIME__Position);
                synth->beatsperbar_type = urid_map->map(urid_map->handle, LV2_TIME__barBeat);
                synth->bpm_type = urid_map->map(urid_map->handle, LV2_TIME__beatsPerMinute);
                synth->speed_type = urid_map->map(urid_map->handle, LV2_TIME__speed);
                synth->frame_type = urid_map->map(urid_map->handle, LV2_TIME__frame);
                synth->framespersec_type = urid_map->map(urid_map->handle, LV2_TIME__framesPerSecond);
                break;
            }
        }
    }
*/
    return synth;
}

void connect_sintar_ports(LV2_Handle handle, uint32_t port, void *data)
{
    SINTAR* synth = (SINTAR*)handle;
    if(port == MIDI_IN)         synth->midi_in_p = (LV2_Atom_Sequence*)data;
    else if(port == OUTPUT)     synth->output_p = (float*)data;
    else if(port == CHANNEL)    synth->channel_p = (float*)data;
    else if(port == MASTER_GAIN)synth->master_gain_p = (float*)data;
    else if(port == RULE)       synth->rule_p = (float*)data;
    else if(port == CELL_LIFE)  synth->cell_life_p = (float*)data;
    else if(port == INIT_CELLS) synth->init_cells_p = (float*)data;
    else if(port == NHARMONICS) synth->nharmonics_p = (float*)data;
    else if(port == HARM_MODE)  synth->harmonic_mode_p = (float*)data;
    else if(port == WAVE)       synth->wave_p = (float*)data;
    else if(port == ENV_A)      synth->env_a_p = (float*)data;
    else if(port == ENV_D)      synth->env_d_p = (float*)data;
    else if(port == ENV_B)      synth->env_b_p = (float*)data;
    else if(port == ENV_SWL)    synth->env_swl_p = (float*)data;
    else if(port == ENV_SUS)    synth->env_sus_p = (float*)data;
    else if(port == ENV_R)      synth->env_r_p = (float*)data;
    else if(port == AMOD_WAV)   synth->amod_wave_p = (float*)data;
    else if(port == AMOD_FREQ)  synth->amod_freq_p = (float*)data;
    else if(port == AMOD_GAIN)  synth->amod_gain_p = (float*)data;
    else if(port == FMOD_WAV)   synth->fmod_wave_p = (float*)data;
    else if(port == FMOD_FREQ)  synth->fmod_freq_p = (float*)data;
    else if(port == FMOD_GAIN)  synth->fmod_gain_p = (float*)data;
    else puts("UNKNOWN PORT YO!!");
}

void run_sintar( LV2_Handle handle, uint32_t nframes)
{
    SINTAR* synth = (SINTAR*)handle;
    unsigned char i,j,k;
    float* buf = synth->output_p;
    LV2_Atom_Event event;
    uint32_t frame_no = 0;
    uint32_t t = 0;
    unsigned char* message;
    unsigned char type;
    unsigned char num, val;
    short bend;
    bool firstnote = true;
    //double astep = synth->waves.func_domain*(*synth->amod_freq_p)/synth->sample_rate;
    //double fstep = synth->waves.func_domain*(*synth->fmod_freq_p)/synth->sample_rate;//need to decide where to calculate this. Probably not here.

    for(t=0;t<nframes;t++)
    {
       /* for(i=0;i<13;i++)
        {
            calc_string(&synth->sympathetic[i],0);
        }
        for(i=0;i<3;i++)
        {
            calc_string(&synth->drone[i],0);
        }
        for(i=0;i<4;i++)
        {
            calc_string(&synth->main[i],0);
        }*/
        calc_string(&synth->main[0],0);
        if(synth->nframessince++ > 44100*5)
        {
            synth->main[0].state[synth->main[0].input] +=.001;
        }


        update_bridge(&synth->bridge);
        buf[t] = synth->bridge.y*333.333;//3mm = saturation

    }
    return;
/*
    synth->ncells = *synth->nharmonics_p;
    synth->cell_lifetime = synth->sample_rate*(*synth->cell_life_p)*synth->ibpm;
    synth->amod_g = *synth->amod_gain_p;
    synth->fmod_g = *synth->fmod_gain_p;


    memset(buf,0, sizeof(float)*nframes);//start by filling buffer with 0s, we'll add to this

    LV2_ATOM_SEQUENCE_FOREACH(synth->midi_in_p, event)
    {
        if (event)
        {
            if(event->body.type == synth->midi_event_type)//make sure its a midi event
            {
                message = (unsigned char*) LV2_ATOM_BODY(&(event->body));
                if( !(*synth->channel_p) || ((message[0]&MIDI_CHANNEL_MASK) == (*synth->channel_p)+1) )
                {
                    type = message[0]&MIDI_TYPE_MASK;
                    t = event->time.frames;

                    if(type == MIDI_NOTE_ON)
                    {
                        num = message[1]&MIDI_DATA_MASK;
                        val = message[2]&MIDI_DATA_MASK;
                        if(firstnote)//only calculate these if there is a note in this period
                        {
                            firstnote = false;
                            //condition envelope
                            synth->envelope[ENV_ATTACK] = 1/(float)(*synth->env_a_p*synth->sample_rate);
                            synth->envelope[ENV_DECAY] = (*synth->env_b_p-1)/(float)(*synth->env_d_p*synth->sample_rate);
                            synth->envelope[ENV_BREAK] = *synth->env_b_p;
                            synth->envelope[ENV_SWELL] = (*synth->env_sus_p - *synth->env_b_p)/(float)(*synth->env_swl_p*synth->sample_rate);
                            synth->envelope[ENV_SUSTAIN] = *synth->env_sus_p;
                            synth->envelope[ENV_RELEASE] = -(*synth->env_sus_p)/(float)(*synth->env_r_p*synth->sample_rate);

                            //set harmonic gains
                            if(*synth->harmonic_mode_p != synth->harmonic_mode)
                            {
                                type = synth->harmonic_mode = *synth->harmonic_mode_p;
                                if(type == HARMONIC_MODE_SINC)
                                {
                                    synth->harm_gains = synth->harm_gain_sinc;
                                }
                                else if(type == HARMONIC_MODE_SAW)
                                {
                                    synth->harm_gains = synth->harm_gain_saw;
                                }
                                else if(type == HARMONIC_MODE_SQR)
                                {
                                    synth->harm_gains = synth->harm_gain_sqr;
                                }
                                else if(type == HARMONIC_MODE_TRI)
                                {
                                    synth->harm_gains = synth->harm_gain_tri;
                                }
                            }
                        }
                        if(val)
                        {
                            if(synth->note[num].note_dead == true)
                            {
                                synth->active[synth->nactive++] = num;//push new note onto active stack
                            }
                            else //note still playing, finish the old one
                            {
                                play_note( &synth->note[num],
                                           &(synth->waves),
                                           t - frame_no,//play to frame before event
                                           &(buf[frame_no]),
                                           synth->pitchbend,
                                           *synth->master_gain_p,
                                           (unsigned char)*synth->rule_p,
                                           *synth->wave_p,
                                           *synth->fmod_wave_p,
                                           fstep,
                                           *synth->amod_wave_p,
                                           astep);//note can't be dead about to start again
                            }
                            start_note(&(synth->note[num]),
                                       &(synth->waves),
                                       val,
                                       t,
                                       synth->harm_gains,
                                       *synth->init_cells_p,
                                       synth->envelope);
                        }
                        else//velocity zero == note off
                        {
                            for(i=0;i<synth->nactive;i++)
                            {
                                if(synth->active[i] == num)
                                {
                                    if(synth->sus)
                                    {
                                        if(!synth->note[num].sus)
                                        {
                                            synth->note[num].sus = true;
                                            synth->sustained[synth->nsustained++] = num;
                                        }
                                    }
                                    else
                                    {
                                        if(t == 0)
                                        {
                                            t++;
                                        }
                                        end_note(&(synth->note[num]),t);
                                    }
                                }
                            }
                        }
                    }
                    else if(type == MIDI_NOTE_OFF)
                    {
                        num = message[1]&MIDI_DATA_MASK;
                        for(i=0;i<synth->nactive;i++)
                        {
                            if(synth->active[i] == num)
                            {
                                if(synth->sus)
                                {
                                    if(!synth->note[num].sus)
                                    {
                                        synth->note[num].sus = true;
                                        synth->sustained[synth->nsustained++] = num;
                                    }
                                }
                                else
                                {
                                    if(t == 0)
                                    {
                                        t++;
                                    }
                                    end_note(&(synth->note[num]),t);
                                }
                            }
                        }

                    }
                    else if(type == MIDI_CONTROL_CHANGE)
                    {
                        num = message[1]&MIDI_DATA_MASK;
                        if(num == MIDI_SUSTAIN_PEDAL)
                        {
                            val = message[2]&MIDI_DATA_MASK;
                            if(val < 64)
                            {
                                synth->sus = false;
                                //end all sus. notes
                                for(i=0;i<synth->nsustained;i++)
                                {
                                    if(synth->note[synth->sustained[i]].sus)
                                    {
                                        if(t == 0)
                                        {
                                            t++;
                                        }
                                        end_note(&(synth->note[synth->sustained[i]]),t);
                                    }
                                }
                                synth->nsustained = 0;
                            }
                            else
                            {
                                synth->sus = true;
                            }
                        }
                        else if(num == MIDI_ALL_NOTES_OFF || num == MIDI_ALL_SOUND_OFF)
                        {
                            if(event->time.frames == 0)
                            {
                                event->time.frames++;
                            }
                            for(i=0;i<synth->nactive;i++)
                            {
                                if(t == 0)
                                {
                                    t++;
                                }
                                num = synth->active[i];
                                end_note(&(synth->note[num]),t);

                            }
                            synth->nactive = 0;
                            synth->nsustained = 0;
                        }

                    }
                    else if(type == MIDI_PITCHBEND)
                    {
                        bend = (message[1]&MIDI_DATA_MASK) + ((message[2]&MIDI_DATA_MASK)<<7) - MIDI_PITCH_CENTER;
                        //run and update current position because this blocks (affects all notes)
                        //run_active_notes
                        for(j=0;j<synth->nactive;j++)
                        {
                            note = &(synth->note[synth->active[j]]);
                            play_note( note,
                                       &(synth->waves),
                                       t - frame_no,//play to frame before event
                                       &(buf[frame_no]),
                                       synth->pitchbend,
                                       *synth->master_gain_p,
                                       (unsigned char)*synth->rule_p,
                                       *synth->wave_p,
                                       *synth->fmod_wave_p,
                                       fstep,
                                       *synth->amod_wave_p,
                                       astep);

                            //cleanup dead notes
                            if(note->note_dead)
                            {
                                synth->nactive--;
                                for(k=j;k<synth->nactive;k++)
                                {
                                    synth->active[k] = synth->active[k+1];
                                }
                            }
                        }
                        synth->pitchbend = myPow2(bend/49152);//49152 is 12*8192/2
                        frame_no = event->time.frames;
                    }//message types
                }//correct channel
            }//actually midi
            else if(event->body.type == synth->other_type)
            {
                // Received new transport position/speed
                const LV2_Atom_Object *obj = (LV2_Atom_Object*)&event->body;
                if(obj->body.otype == synth->time_info_type)
                {
                    LV2_Atom *beat = NULL, *bpm = NULL, *speed = NULL;
                    LV2_Atom *fps = NULL, *frame = NULL;
                    lv2_atom_object_get(obj,
                                        synth->beatsperbar_type, &beat,
                                        synth->bpm_type, &bpm,
                                        synth->speed_type, &speed,
                                        synth->frame_type, &frame,
                                        synth->framespersec_type, &fps,
                                        NULL);

                    if (fps && fps->type == synth->float_type)
                    {
                        synth->sample_rate = ((LV2_Atom_Float*)frame)->body;
                    }
                    if (bpm && bpm->type == synth->float_type)
                    {
                        // Tempo changed, update BPM
                        synth->ibpm = 60/(((LV2_Atom_Float*)bpm)->body);
                        synth->cell_lifetime = synth->sample_rate*(*synth->cell_life_p)*synth->ibpm;
                    }
                    /*if (speed && speed->type == synth->float_type) {
                        // Speed changed, e.g. 0 (stop) to 1 (play)
                        self->speed = ((LV2_Atom_Float*)speed)->body;
                    }//could use this to end all notes, but midi message is good enough
                    if (beat && beat->type == synth->float_type) {
                       const double samples_per_beat = 60.0 / self->bpm * self->samplerate;
                        self->bar_beats = ((LV2_Atom_Float*)beat)->body;
                        self->beat_beats = self->bar_beats - floor(self->bar_beats);
                        self->pos_bbt = self->beat_beats * samples_per_beat;
                    }*/
                    /*if (frame && frame->type == synth->long_type) {
                        self->pos_frame = ((LV2_Atom_Long*)frame)->body;
                    }
                }//if time position
            }//if blank type
        }//actually is event
    }//for each event

    //finish off whatever frames are left
    if(frame_no != nframes-1)
    {
        //run_active_notes
        for(j=0;j<synth->nactive;j++)
        {
            note = &(synth->note[synth->active[j]]);
            play_note( note,
                       &(synth->waves),
                       nframes - frame_no,
                       &(buf[frame_no]),
                       synth->pitchbend,
                       *synth->master_gain_p,
                       (unsigned char)*synth->rule_p,
                       *synth->wave_p,
                       *synth->fmod_wave_p,
                       fstep,
                       *synth->amod_wave_p,
                       astep);

            //cleanup dead notes
            if(note->note_dead)
            {
                synth->nactive--;
                for(k=j;k<synth->nactive;k++)
                {
                    synth->active[k] = synth->active[k+1];
                }
                j--;//indexes changed
            }
        }//active notes
    }//leftovers
*/
}


void cleanup_sintar(LV2_Handle handle)
{
    SINTAR* synth = (SINTAR*) handle;
    unsigned char i;
    for(i=0;i<13;i++)
    {
        cleanup_string(&synth->sympathetic[i]);
    }
    for(i=0;i<3;i++)
    {
        cleanup_string(&synth->drone[i]);
    }
    for(i=0;i<4;i++)
    {
        cleanup_string(&synth->main[i]);
    }
    free(synth);
}
