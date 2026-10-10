// ==== entry @ 00010000 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  undefined4 extraout_A0;
  undefined4 *puVar4;
  
  uVar2 = FUN_00021fa0();
  sVar3 = 0x4e3;
  puVar4 = &DAT_00026bb0;
  do {
    *puVar4 = 0;
    iVar1 = _DAT_00000004;
    sVar3 = sVar3 + -1;
    puVar4 = puVar4 + 1;
  } while (sVar3 != -1);
  DAT_00026ec4 = _DAT_00000004;
  DAT_00027f02 = (undefined1 *)register0x0000003c;
  if ((*(byte *)(_DAT_00000004 + 0x129) & 0x10) != 0) {
    (**(code **)(_DAT_00000004 + -0x1e))(uVar2,extraout_A0);
  }
  DAT_00026e6e = (**(code **)(iVar1 + -0x198))();
  if (DAT_00026e6e == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== FUN_00010006 @ 00010006 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00010006(undefined4 param_1)

{
  short sVar1;
  char cVar2;
  
  DAT_00bfe001 = DAT_00bfe001 | 2;
  (*_thunk_FUN_0001aa50)();
  open_libraries_and_sound();
  (**(code **)(DAT_00026e76 + -0x4e))();
  not_in_game = 0xff;
  install_vbl_server();
  DAT_00024bfc = 0xffff;
  if (1 < param_1._0_2_) {
    DAT_00026ed6 = &DAT_000233a8;
  }
  (*_thunk_FUN_0001ccb6)();
  init_display_memory();
  DAT_00026dd6 = (undefined1 *)register0x0000003c;
  FUN_000134bc();
  (*_thunk_FUN_00018022)();
LAB_00010066:
  do {
    FUN_00011234();
    sound_off = 0;
    abort_to_rank_select = '\0';
    demo_mode = 0;
    demo_tick_budget = 0;
    DAT_000254f0._0_1_ = 0;
    DAT_00025504._0_1_ = 0;
    new_game_init();
    game_over_display = 0;
    _session_over = 0;
    DAT_00025511 = 0;
    enemy_planes_destroyed = 0;
    (*_rank_select_screen)();
    load_dash_shapes();
    if (DAT_00026c90 == 0) {
      (*_load_map)();
    }
    sVar1 = (*_mission_briefing_screen)();
  } while (sVar1 != 0);
  (*_thunk_FUN_0001edaa)();
  (*_setup_level_display)();
  (*_load_ship_shapes)();
  FUN_0001535a();
  (*_load_sounds)();
  if (DAT_00026c90 != 0) goto LAB_000100ea;
  do {
    reset_enemy_state();
    rearm_new_plane();
    paused = '\0';
    soldiers_killed = 0;
    input_word = 0;
LAB_000100ea:
    not_in_game = 0;
    DAT_00026c90 = 0;
    (*_logic_tick)();
    (*_input_queue_clear)();
    if (demo_mode != 0) {
      demo_tick_budget = 2;
    }
    DAT_00026ca4 = CONCAT11(0xff,(undefined1)DAT_00026ca4);
LAB_0001010e:
    (*_keyboard_commands)();
    if (session_over != '\0') {
LAB_000101c6:
      (*_sound_stop_all)();
      clear_ticker();
      FUN_000173e6();
      DAT_00026ca4 = 0;
      demo_playback_flag = -(demo_mode == 1);
      (*_finish_demo_recording)();
      if (_quit_program != 0) {
        DAT_00bfe001 = DAT_00bfe001 & 0xfd;
        music_stop_unload();
        FUN_00011234();
        FUN_000134d8();
        return;
      }
      not_in_game = 0xff;
      ticker_message = 0;
      if (demo_playback_flag == '\0') {
        FUN_00011234();
        (*_high_score_screen)();
      }
      goto LAB_00010066;
    }
    if (paused != '\0') {
      (*_wait_next_vbl)();
      goto LAB_0001010e;
    }
    if ((carrier_menu_active == '\0') || (mission_complete == 0)) {
      frame_update_and_render();
      run_queued_logic_ticks();
      if (abort_to_rank_select != '\0') goto LAB_00010066;
      if (((demo_mode == 1) && (sVar1 = (*_thunk_FUN_0002044c)(), sVar1 != 0)) ||
         (session_over != '\0')) goto LAB_000101c6;
      goto LAB_0001010e;
    }
    mission_complete = 0;
    carrier_menu_active = '\0';
    (*_sound_stop_all)();
    ticker_message = 0;
    clear_ticker();
    FUN_000173e6();
    FUN_00011234();
    if (victory_balloons != '\0') {
      lives = lives + '\x01';
    }
    choose_night_flag();
    (*_thunk_FUN_0001edaa)();
    (*_load_map)();
    cVar2 = (*_mission_briefing_screen)();
    if (cVar2 != '\0') goto LAB_00010066;
    load_dash_shapes();
    (*_setup_level_display)();
    (*_load_ship_shapes)();
    FUN_0001535a();
    (*_load_sounds)();
  } while( true );
}


// ==== FUN_0001020e @ 0001020e ====

void FUN_0001020e(void)

{
  DAT_00bfe001 = DAT_00bfe001 & 0xfd;
  music_stop_unload();
  FUN_00011234();
  FUN_000134d8();
  return;
}


// ==== frame_update_and_render @ 00010228 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void frame_update_and_render(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined2 uVar3;
  
  (*_wait_vbl_flag)();
  frame_counter_mod11 = frame_counter_mod11 + 1;
  if (10 < frame_counter_mod11) {
    frame_counter_mod11 = 0;
  }
  (*_clip_playfield)();
  (*_set_rastport)();
  snapshot_logic_state_for_render();
  zoom_shift = 0;
  if (view_scale == 1) {
    zoom_shift = 3;
  }
  camera_left_x = render_player_x + (-0xa0 << zoom_shift);
  if (view_scale == 1) {
    waterline_y = 0x97;
    camera_ref_y = 0x4b8;
  }
  else {
    waterline_y = 0x97;
    camera_ref_y = waterline_y;
    if (0x83 < render_player_y) {
      waterline_y = render_player_y + 0x14;
      camera_ref_y = waterline_y;
    }
  }
  (*_update_waterline_split)();
  if (DAT_00024e74 != '\0') {
    carrier_alive = 0xffff;
    respawn_on_carrier();
    DAT_00024e74 = '\0';
  }
  (*_render_world)();
  update_draw_debris();
  (*_update_draw_soldiers)();
  (*_draw_splashes)();
  draw_projectiles();
  draw_weapon_select_box();
  (*_draw_balloons)();
  draw_game_over();
  (*_clip_dashboard)();
  (*_set_rastport)();
  (*_draw_3d_view)();
  (*_draw_dashboard)();
  DAT_00026d8c = 0xff;
  uVar3 = *(undefined2 *)(*(int *)(back_playfield_viewport + 0x98) + 2);
  if ((sky_flash_count != 0) &&
     (uVar1 = sky_flash_count - 1, uVar2 = sky_flash_count & 1, sky_flash_count = uVar1, uVar2 != 0)
     ) {
    uVar3 = sky_flash_color;
  }
  *(undefined2 *)(*(int *)(back_view + 2) + 0x92) = uVar3;
  (*_present_frame)();
  return;
}


// ==== FUN_0001030c @ 0001030c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001030c(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined2 uVar3;
  
  uVar3 = *(undefined2 *)(*(int *)(back_playfield_viewport + 0x98) + 2);
  if ((sky_flash_count != 0) &&
     (uVar1 = sky_flash_count - 1, uVar2 = sky_flash_count & 1, sky_flash_count = uVar1, uVar2 != 0)
     ) {
    uVar3 = sky_flash_color;
  }
  *(undefined2 *)(*(int *)(back_view + 2) + 0x92) = uVar3;
  (*_present_frame)();
  return;
}


// ==== draw_weapon_select_box @ 00010344 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_weapon_select_box(void)

{
  if ((carrier_menu_active != '\0') && (mission_complete == 0)) {
    (*_own_blitter)();
    (*_blit_shape)();
    (*_blit_shape)();
    (*_wait_disown_blitter)();
  }
  return;
}


// ==== draw_player_plane @ 000103a6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_player_plane(void)

{
  byte bVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  short sVar4;
  undefined2 extraout_D1w;
  ushort uVar5;
  short sVar6;
  ushort *puVar7;
  
  uVar2 = clip_bottom;
  if ((((player_state == 1) || (player_state == 7)) || (player_state == 0xb)) || (player_state == 8)
     ) {
LAB_0001045c:
    render_player_y = player_y;
  }
  else {
    if (carrier_phase == 1) {
      return;
    }
    if ((zoom_shift != 0) || ((short)render_player_x < 0)) goto LAB_0001045c;
    puVar7 = (ushort *)((short)((render_player_x >> 3) * 2) + DAT_00024578);
    if ((puVar7 < DAT_0002457c) && ((*puVar7 & 3) == 1)) {
      (*_ship_num_from_map_ptr)(puVar7);
    }
  }
  clip_bottom = 0xa1;
  uVar3 = player_shape_ptr;
  if (view_scale != 1) goto LAB_000104f6;
  if (render_turn_frame == 0) {
    sVar6 = -DAT_00026ecc >> 2;
    if (sVar6 < -2) {
      sVar6 = -2;
    }
    if (-1 < render_player_dir) {
      sVar6 = sVar6 + 6;
    }
    sVar6 = sVar6 + 0x2a;
  }
  else {
    uVar5 = render_turn_frame;
    if (8 < render_turn_frame) {
      if (render_turn_frame < 0x12) {
        sVar4 = render_player_dir;
        if (0xd < render_turn_frame) {
          sVar4 = -render_player_dir;
        }
        sVar6 = render_turn_frame + 0x2f;
        if (-1 < sVar4) {
          sVar6 = render_turn_frame + 0x38;
        }
        goto LAB_000104e2;
      }
      uVar5 = 0x1a - render_turn_frame;
    }
    sVar4 = (short)(uVar5 - 1) >> 2;
    sVar6 = sVar4 + 0x34;
    if (-1 < render_player_dir) {
      sVar6 = sVar4 + 0x36;
    }
  }
LAB_000104e2:
  uVar3 = *(undefined4 *)(eighth_frames + (short)(sVar6 << 2));
LAB_000104f6:
  (*_clip_to_deck)(uVar3);
  if ((((render_turn_frame == 0) && (weapon_type == 2)) && (ordnance_count != '\0')) &&
     (zoom_shift == 0)) {
    (*_draw_shape_automask)();
  }
  if (((render_turn_frame == 0) && (zoom_shift == 0)) &&
     ((player_state == 0 || ((player_state == 7 || (deck_tail_up != 0)))))) {
    if (gear_anim != gear_target) {
      if (gear_anim < gear_target) {
        gear_anim = gear_anim + 2;
      }
      gear_anim = gear_anim + -1;
    }
    (*_draw_shape_automask)();
  }
  (*_draw_shape_automask)();
  if (player_state == 7) {
    (*_draw_line_clipped)(extraout_D1w);
  }
  if ((((render_turn_frame != 0) && (weapon_type == 2)) && (ordnance_count != '\0')) &&
     (zoom_shift == 0)) {
    (*_draw_shape_automask)();
  }
  uVar3 = (*_clip_playfield)();
  if (((gun_firing != 0) && (render_turn_frame == 0)) &&
     ((view_scale != 1 &&
      (bVar1 = DAT_000252d8 + 1, DAT_000252d8 = bVar1 & 3,
      (&DAT_00024b58)[(short)((ushort)CONCAT31((int3)((uint)uVar3 >> 8),bVar1) & 0xff03)] != '\0')))
     ) {
    (*_blit_shape_xor)();
  }
  clip_bottom = uVar2;
  return;
}


// ==== draw_projectiles @ 000106be ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_projectiles(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  (*_own_blitter)();
  if (DAT_000252bc != '\0') {
    DAT_000252bc = '\0';
  }
  puVar2 = &projectiles;
  sVar1 = 0xe;
  do {
    if (*(char *)(puVar2 + 6) != '\0') {
      draw_projectile();
    }
    puVar2 = puVar2 + 0x15;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if (DAT_000254f0._0_1_ != '\0') {
    draw_projectile();
  }
  (*_wait_disown_blitter)();
  return;
}


// ==== draw_projectile @ 00010702 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_projectile(void)

{
  char cVar1;
  int unaff_A2;
  
  if (((*(short *)(unaff_A2 + 0x22) == 1) || (*(short *)(unaff_A2 + 0x22) != 2)) ||
     (*(char *)(unaff_A2 + 0x1e) != '\n')) {
    if (*(char *)(unaff_A2 + 0xc) == '\b') {
      cVar1 = *(char *)(unaff_A2 + 0x21) + '\x01';
      if (cVar1 == '\b') {
        *(undefined1 *)(unaff_A2 + 0x20) = 0;
        *(undefined1 *)(unaff_A2 + 0x21) = 0;
        return;
      }
      *(char *)(unaff_A2 + 0x21) = cVar1;
    }
    (*_draw_world_object)();
  }
  return;
}


// ==== find_free_projectile_slot @ 000107d4 ====

undefined2 * find_free_projectile_slot(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  puVar2 = &projectiles;
  sVar1 = 0xe;
  do {
    if (*(char *)(puVar2 + 0x10) == '\0') {
      return puVar2;
    }
    puVar2 = puVar2 + 0x15;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return (undefined2 *)0x0;
}


// ==== fire_weapon @ 000107f2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fire_weapon(void)

{
  short sVar2;
  undefined1 uVar4;
  int iVar1;
  ushort uVar3;
  char cVar5;
  undefined4 *puVar6;
  int extraout_A0;
  int extraout_A0_00;
  
  DAT_00026eda = 0x14;
  if (ordnance_count != '\0') {
    puVar6 = (undefined4 *)&projectiles;
    sVar2 = 0xe;
    do {
      if (*(char *)(puVar6 + 8) == '\0') {
        if (ordnance_count != -1) {
          ordnance_count = ordnance_count + -1;
        }
        *(undefined2 *)((int)puVar6 + 0x22) = weapon_type;
        *(undefined4 *)((int)puVar6 + 0x12) = DAT_00026db2;
        *(undefined4 *)((int)puVar6 + 0xe) = DAT_00026db6;
        if (player_dir < 0) {
          *(int *)((int)puVar6 + 0xe) = -*(int *)((int)puVar6 + 0xe);
        }
        *(undefined2 *)(puVar6 + 1) = render_player_y;
        *(short *)(puVar6 + 1) = *(short *)(puVar6 + 1) + 0xb;
        *puVar6 = DAT_00026dba;
        uVar4 = 3;
        if (-1 < *(char *)((int)puVar6 + 0xe)) {
          uVar4 = 9;
        }
        *(undefined1 *)((int)puVar6 + 0x1e) = uVar4;
        if (*(short *)((int)puVar6 + 0x22) != 1) {
          if (*(short *)((int)puVar6 + 0x22) != 2) {
            *(short *)((int)puVar6 + 0x26) = pitch_binary_angle >> 1;
            *(undefined2 *)(puVar6 + 10) = player_airspeed;
            sVar2 = (*_sin_lookup)();
            *(int *)(extraout_A0 + 0x1a) = sVar2 * 0x10 >> 3;
            sVar2 = (*_cos_lookup)();
            iVar1 = sVar2 * 0x10 >> 3;
            if (*(short *)(extraout_A0_00 + 0xe) < 0) {
              iVar1 = -iVar1;
            }
            *(int *)(extraout_A0_00 + 0x16) = iVar1;
            (*_thunk_FUN_000203be)();
            (*_thunk_FUN_000203be)();
            (*_thunk_FUN_000203be)();
            uVar3 = (*_thunk_FUN_000203be)();
            sVar2 = (uVar3 & 6) << 1;
            if ((uVar3 & 6) == 0) {
              sVar2 = 8;
            }
            *(short *)(extraout_A0_00 + 0x24) = sVar2;
            sVar2 = 4 - (pitch_binary_angle >> 5);
            if (4 < pitch_binary_angle >> 5) {
              sVar2 = 0;
            }
            if (9 < sVar2) {
              sVar2 = 9;
            }
            cVar5 = (char)sVar2;
            if (*(char *)(extraout_A0_00 + 0xe) < '\0') {
              cVar5 = cVar5 + '\n';
            }
            *(char *)(extraout_A0_00 + 0x1e) = cVar5;
            *(undefined1 *)(extraout_A0_00 + 0x20) = 0xff;
            return;
          }
          *(undefined1 *)((int)puVar6 + 0x1f) = (undefined1)player_dir;
        }
        *(undefined1 *)(puVar6 + 8) = 0xff;
        return;
      }
      puVar6 = (undefined4 *)((int)puVar6 + 0x2a);
      sVar2 = sVar2 + -1;
    } while (sVar2 != -1);
  }
  return;
}


// ==== spawn_explosion_at_cell @ 00010820 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void spawn_explosion_at_cell(short param_1,undefined4 param_2)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  
  sVar1 = (short)DAT_00024578;
  psVar3 = &projectiles;
  sVar2 = 0xe;
  while (*(char *)(psVar3 + 0x10) != '\0') {
    psVar3 = psVar3 + 0x15;
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return;
    }
  }
  psVar3[9] = 0;
  psVar3[10] = 0;
  psVar3[7] = 0;
  psVar3[8] = 0;
  *psVar3 = (param_1 - sVar1) * 4;
  psVar3[2] = param_2._0_2_ + 0xc;
  psVar3[0xf] = 0;
  *(undefined1 *)(psVar3 + 0x10) = 8;
  *(undefined1 *)((int)psVar3 + 0x21) = 1;
  psVar3[0x11] = 1;
  *(undefined1 *)((int)psVar3 + 0x1f) = 0;
  if (param_2._2_2_ != 0) {
    return;
  }
  *(undefined1 *)((int)psVar3 + 0x1f) = 2;
                    /* WARNING: Could not recover jumptable at 0x00010888. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_sfx_boom)();
  return;
}


// ==== rocket_ignite_and_aim @ 0001099a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void rocket_ignite_and_aim(void)

{
  int iVar1;
  short sVar2;
  ushort uVar3;
  int in_A0;
  
  if ((((*(short *)(in_A0 + 0x26) >> 1 < 0) && (sVar2 = gun_ground_impact_x(), sVar2 != 0)) &&
      (sVar2 = gun_ground_impact_x(), sVar2 != 0)) &&
     ((sVar2 = gun_ground_impact_x(), sVar2 != 0 &&
      (((sVar2 = find_ship_gun_in_range(), sVar2 != 0 ||
        (sVar2 = find_ship_gun_in_range(), sVar2 != 0)) ||
       ((sVar2 = find_pillbox_in_range(), sVar2 != 0 ||
        (sVar2 = find_pillbox_in_range(), sVar2 != 0)))))))) {
    atan2_lookup();
    uVar3 = *(ushort *)(in_A0 + 0x28) / 100;
    sVar2 = (*_cos_lookup)();
    iVar1 = *(int *)(in_A0 + 0xe);
    *(int *)(in_A0 + 0xe) = (int)sVar2 * (int)(short)uVar3;
    if (iVar1 < 0) {
      *(int *)(in_A0 + 0xe) = -*(int *)(in_A0 + 0xe);
    }
    sVar2 = (*_sin_lookup)();
    *(int *)(in_A0 + 0x12) = (int)sVar2 * (int)(short)uVar3;
  }
  *(undefined1 *)(in_A0 + 0x20) = 0xff;
  return;
}


// ==== update_projectiles @ 00010a72 ====

void update_projectiles(void)

{
  short sVar1;
  undefined2 *extraout_A0;
  undefined2 *puVar2;
  
  puVar2 = &projectiles;
  sVar1 = 0xe;
  do {
    if (*(char *)(puVar2 + 0x10) != '\0') {
      update_projectile();
      puVar2 = extraout_A0;
    }
    puVar2 = puVar2 + 0x15;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00026d8c = 0;
  if (DAT_00025504._0_1_ != '\0') {
    update_projectile();
  }
  return;
}


// ==== update_projectile @ 00010aa6 ====

/* WARNING: Removing unreachable block (ram,0x00010c36) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_projectile(void)

{
  int iVar1;
  short sVar4;
  int iVar2;
  short sVar5;
  short sVar6;
  undefined4 uVar3;
  char cVar7;
  int *in_A0;
  undefined4 extraout_A0;
  
  if (*(char *)(in_A0 + 8) == '\b') {
    return;
  }
  if (*(short *)((int)in_A0 + 0x22) == 0) {
    if (*(short *)(in_A0 + 9) == 0) {
LAB_00010aec:
      *(int *)((int)in_A0 + 0x12) = *(int *)((int)in_A0 + 0x1a) + *(int *)((int)in_A0 + 0x12);
      *(int *)((int)in_A0 + 0xe) = *(int *)((int)in_A0 + 0x16) + *(int *)((int)in_A0 + 0xe);
    }
    else {
      sVar4 = *(short *)(in_A0 + 9) + -1;
      *(short *)(in_A0 + 9) = sVar4;
      if (sVar4 == 0) {
        rocket_ignite_and_aim();
        goto LAB_00010aec;
      }
      sVar4 = 1;
      if (player_dir < 0) {
        sVar4 = -1;
      }
      *(short *)in_A0 = *(short *)in_A0 - sVar4;
      *(short *)(in_A0 + 1) = *(short *)(in_A0 + 1) + -1;
    }
    iVar2 = *in_A0 + *(int *)((int)in_A0 + 0xe);
    *in_A0 = iVar2;
    iVar2 = _render_player_x - iVar2;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    sVar5 = (short)((uint)iVar2 >> 0x10);
    sVar4 = sVar5 + -0x280;
    if (zoom_shift != 0) {
      sVar4 = sVar5 + -0x1400;
    }
    if (0x280 < sVar4) {
      *(undefined1 *)(in_A0 + 8) = 0;
      return;
    }
    sVar4 = (short)((uint)(in_A0[1] + *(int *)((int)in_A0 + 0x1a) + *(int *)((int)in_A0 + 0x12)) >>
                   0x10);
  }
  else {
    if ((*(short *)((int)in_A0 + 0x22) == 2) && (*(char *)((int)in_A0 + 0x1e) == '\n'))
    goto LAB_00010d50;
    iVar2 = *(int *)((int)in_A0 + 0xe) +
            ((int)(short)((uint)*(int *)((int)in_A0 + 0xe) >> 0x10) / 10) * -0x10000;
    *(int *)((int)in_A0 + 0xe) = iVar2;
    *in_A0 = iVar2 + *in_A0;
    iVar2 = *(int *)((int)in_A0 + 0x12) - gravity;
    *(int *)((int)in_A0 + 0x12) = iVar2;
    sVar4 = (short)((uint)(in_A0[1] + iVar2) >> 0x10);
  }
  iVar2 = find_zone_at_x();
  if (iVar2 == 0) {
    *(short *)(in_A0 + 1) = sVar4;
    sVar5 = (*_map_cell_at_x)();
    if (sVar5 == 0) {
      sVar6 = 0xc;
    }
    else if (sVar5 == 2) {
      sVar6 = 0xc;
    }
    else if (sVar5 == 1) {
      sVar6 = object_height_at_cell_a0(extraout_A0);
      sVar6 = sVar6 + 0xb;
    }
    else {
      sVar6 = 0xc;
    }
    if (sVar4 <= sVar6) {
      *(short *)(in_A0 + 1) = sVar6;
      cVar7 = (char)sVar5;
      *(char *)((int)in_A0 + 0x1f) = cVar7;
      if ((cVar7 == '\x02') || (cVar7 != '\0')) {
        (*_sfx_boom)();
      }
      else {
        (*_sfx_splash)();
      }
      *(ushort *)((int)in_A0 + 0x1a) = frame_counter_mod100;
      if ((*(short *)((int)in_A0 + 0x22) == 2) && (cVar7 == '\0')) {
        if (*(char *)((int)in_A0 + 0x1e) != '\n') {
          if (*(short *)((int)in_A0 + 0x12) < -5) goto LAB_00010cae;
          uVar3 = 0x45000;
          if (*(short *)((int)in_A0 + 0xe) < 0) {
            uVar3 = 0xfffbb000;
          }
          *(undefined4 *)((int)in_A0 + 0xe) = uVar3;
          *(undefined1 *)((int)in_A0 + 0x1e) = 10;
          *(undefined4 *)((int)in_A0 + 0x12) = 200;
          if (frame_counter_mod100 != *(ushort *)((int)in_A0 + 0x1a)) {
            *(ushort *)((int)in_A0 + 0x1a) = frame_counter_mod100;
            (*_add_gun_impact)();
          }
        }
LAB_00010d50:
        iVar2 = *(int *)((int)in_A0 + 0x12);
        iVar1 = iVar2 + -1;
        *(int *)((int)in_A0 + 0x12) = iVar1;
        if (iVar1 == 0 || iVar2 < 1) {
          *(undefined1 *)(in_A0 + 8) = 0;
          *(undefined1 *)((int)in_A0 + 0x21) = 0;
        }
        else {
          *in_A0 = *in_A0 + *(int *)((int)in_A0 + 0xe);
          cVar7 = (*_map_cell_at_x)();
          if (cVar7 != '\0') {
            (*_weapon_impact_ground_objects)();
            *(undefined1 *)(in_A0 + 8) = 8;
            *(undefined1 *)((int)in_A0 + 0x21) = 1;
            (*_sfx_boom)();
            (*_sfx_splash)();
            return;
          }
        }
        (*_add_gun_impact)();
        return;
      }
LAB_00010cae:
      (*_weapon_impact_ground_objects)();
      *(undefined1 *)(in_A0 + 8) = 8;
      *(undefined1 *)((int)in_A0 + 0x21) = 1;
      kill_soldiers_near();
      return;
    }
  }
  else if (sVar4 < 0x1f) {
    if (*(short *)((int)in_A0 + 0x22) != 0) {
      *(undefined2 *)(in_A0 + 1) = 0x1e;
      *(int *)((int)in_A0 + 0x12) = -*(int *)((int)in_A0 + 0x12);
      *(short *)((int)in_A0 + 0x12) = *(short *)((int)in_A0 + 0x12) >> 1;
      if (*(short *)((int)in_A0 + 0x12) < 9) {
        if (*(short *)((int)in_A0 + 0x12) == 0) {
          *(undefined1 *)(in_A0 + 8) = 0;
          goto LAB_00010cca;
        }
      }
      else {
        *(undefined2 *)((int)in_A0 + 0x12) = 9;
      }
      sVar4 = *(short *)((int)in_A0 + 0xe) >> 1;
      *(short *)((int)in_A0 + 0xe) = sVar4;
      if (sVar4 != 0) goto LAB_00010cca;
    }
    *(undefined1 *)(in_A0 + 8) = 0;
  }
  else {
    *(short *)(in_A0 + 1) = sVar4;
  }
LAB_00010cca:
  if ((((*(short *)((int)in_A0 + 0x22) == 1) && (DAT_00026d8c != '\0')) &&
      ((frame_counter_mod100 & 1) != 0)) &&
     (*(char *)((int)in_A0 + 0x1e) = *(char *)((int)in_A0 + 0x1e) + '\x01',
     0xb < *(byte *)((int)in_A0 + 0x1e))) {
    *(undefined1 *)((int)in_A0 + 0x1e) = 0;
  }
  return;
}


// ==== draw_enemy_planes_and_wrecks @ 00010da6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_enemy_planes_and_wrecks(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  short sVar2;
  short *psVar3;
  short *psVar4;
  
  psVar4 = &wreck_list;
  sVar2 = wreck_count;
  while (sVar2 = sVar2 + -1, sVar2 != -1) {
    psVar3 = psVar4 + 1;
    sVar1 = *psVar4;
    if (sVar1 < 0) {
      sVar1 = -sVar1;
    }
    sVar1 = sVar1 - camera_left_x;
    if (zoom_shift != 0) {
      sVar1 = sVar1 >> 3;
    }
    psVar4 = psVar3;
    if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
      (*_draw_shape_automask)();
    }
  }
  sVar2 = 3;
  psVar4 = &enemy_planes;
  do {
    if (*psVar4 != 0) {
      sVar1 = psVar4[0x10] - camera_left_x;
      if (zoom_shift != 0) {
        sVar1 = sVar1 >> 3;
      }
      if ((((-0x81 < sVar1) && (sVar1 < 0x1c1)) && ((*_draw_shape_automask)(), psVar4[9] != 0)) &&
         ((zoom_shift == 0 && (psVar4[0x16] = psVar4[0x16] + 1, (psVar4[0x16] & 1U) != 0)))) {
        (*_blit_shape_xor)();
      }
    }
    psVar4 = psVar4 + 0x1a;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== update_draw_debris @ 00010ee0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 update_draw_debris(void)

{
  short sVar1;
  short sVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar3;
  int *extraout_A1;
  int *piVar4;
  
  (*_own_blitter)();
  sVar2 = clip_bottom;
  if (carrier_phase != 0) {
    clip_bottom = DAT_00025442 + wave_bob_offset + 0x84;
  }
  sVar3 = 0x27;
  piVar4 = smoke_particles_ptr;
  do {
    if (*(short *)(piVar4 + 4) != 0) {
      (*_draw_world_object)();
      *extraout_A1 = extraout_A1[2] + *extraout_A1;
      extraout_A1[1] = extraout_A1[3] + extraout_A1[1];
      sVar1 = *(short *)((int)extraout_A1 + 0x12) + -1;
      *(short *)((int)extraout_A1 + 0x12) = sVar1;
      piVar4 = extraout_A1;
      if (sVar1 < 0) {
        *(undefined2 *)((int)extraout_A1 + 0x12) = 6;
        *(short *)(extraout_A1 + 4) = *(short *)(extraout_A1 + 4) + -1;
      }
    }
    sVar3 = sVar3 + -1;
    piVar4 = piVar4 + 5;
  } while (sVar3 != -1);
  clip_bottom = sVar2;
  (*_wait_disown_blitter)();
  return CONCAT44(in_D0,in_D1);
}


// ==== snapshot_logic_state_for_render @ 00010f88 ====

void snapshot_logic_state_for_render(void)

{
  int iVar1;
  short sVar2;
  undefined2 *puVar3;
  undefined **ppuVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  iVar1 = DAT_00026ec4;
  (**(code **)(DAT_00026ec4 + -0x84))();
  render_player_x = player_x;
  render_player_y = player_y;
  render_player_dir = player_dir;
  render_turn_frame = turn_frame;
  DAT_00026ecc = DAT_00026db2._0_2_;
  wave_bob_offset = wave_bob;
  view_scale = zoom_request;
  puVar3 = &projectiles;
  sVar2 = 0xe;
  do {
    puVar3[4] = *puVar3;
    puVar3[5] = puVar3[2];
    puVar3[6] = puVar3[0x10];
    puVar3 = puVar3 + 0x15;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  DAT_000254ec = enemy_bomb_object;
  DAT_000254ee = DAT_000254e8;
  DAT_000254f0 = DAT_00025504;
  puVar3 = &enemy_planes;
  sVar2 = 3;
  do {
    puVar3[0x17] = ((short)puVar3[0x10] >> 3) * 2;
    puVar3 = puVar3 + 0x1a;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  sVar2 = 3;
  puVar3 = &airfield_zones;
  do {
    *(undefined4 *)(puVar3 + 8) = *(undefined4 *)(puVar3 + 3);
    puVar3 = puVar3 + 10;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  sVar2 = 4;
  ppuVar4 = &ship_ptr_list;
  do {
    *(undefined2 *)(*ppuVar4 + 0x1a) = *(undefined2 *)(*ppuVar4 + 0x14);
    sVar2 = sVar2 + -1;
    ppuVar4 = ppuVar4 + 1;
  } while (sVar2 != -1);
  puVar5 = &ship_plane_blocks;
  puVar7 = &ship_plane_blocks_render_copy;
  sVar2 = 4;
  do {
    *puVar7 = *puVar5;
    puVar7[1] = puVar5[1];
    puVar7[2] = puVar5[2];
    puVar7[3] = puVar5[3];
    puVar7[4] = puVar5[4];
    puVar7[5] = puVar5[5];
    puVar7[6] = puVar5[6];
    puVar7[7] = puVar5[7];
    puVar7[8] = puVar5[8];
    puVar7[9] = puVar5[9];
    puVar7[10] = puVar5[10];
    puVar7[0xb] = puVar5[0xb];
    puVar7[0xc] = puVar5[0xc];
    puVar7[0xd] = puVar5[0xd];
    puVar6 = puVar5 + 0xf;
    puVar8 = puVar7 + 0xf;
    puVar7[0xe] = puVar5[0xe];
    puVar5 = puVar5 + 0x10;
    puVar7 = puVar7 + 0x10;
    *puVar8 = *puVar6;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  (**(code **)(iVar1 + -0x8a))();
  wave_frame_delay = wave_frame_delay + -1;
  if (wave_frame_delay < '\0') {
    wave_frame = wave_frame + -1;
    if (wave_frame < '\0') {
      wave_frame = '\v';
    }
    wave_frame_delay = '\x01';
  }
  return;
}


// ==== fire_ordnance @ 0001107c ====

undefined8 fire_ordnance(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_000252bc = 0xff;
  fire_weapon();
  DAT_00026d8d = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00011092 @ 00011092 ====

undefined8 FUN_00011092(void)

{
  uint in_D0;
  uint in_D1;
  uint uVar1;
  int iVar2;
  
  uVar1 = (in_D1 & 0xffff) * (in_D0 & 0xffff);
  iVar2 = (int)(short)in_D1 * (int)(short)(in_D0 >> 0x10);
  if (((short)uVar1 < 0) && (uVar1 = uVar1 + 0x10000, uVar1 == 0)) {
    iVar2 = iVar2 + 1;
  }
  return CONCAT44((uVar1 >> 0x10) + iVar2,in_D1);
}


// ==== draw_game_over @ 000110c2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_game_over(void)

{
  int iVar1;
  bool bVar2;
  
  if (game_over_display != '\0') {
    (*_own_blitter)();
    (*_clip_playfield)();
    (*_set_rastport)();
    iVar1 = (*_find_shape_by_name)();
    if (iVar1 != 0) {
      (*_draw_shape_automask)();
    }
    (*_wait_disown_blitter)();
    if (game_over_countdown != 0) {
      bVar2 = SBORROW1(game_over_countdown,'\x01');
      game_over_countdown = game_over_countdown - 1;
      if (game_over_countdown == 0 || bVar2 != (short)((ushort)game_over_countdown << 8) < 0) {
        session_over = 0xff;
      }
    }
  }
  return;
}


// ==== find_zone_at_x @ 00011126 ====

short * find_zone_at_x(void)

{
  short in_D0w;
  short sVar1;
  short *psVar2;
  
  psVar2 = &airfield_zones;
  sVar1 = 3;
  do {
    if (*psVar2 == 0) {
      return (short *)0x0;
    }
    if (in_D0w < *psVar2) {
      return (short *)0x0;
    }
    if (in_D0w <= psVar2[1]) {
      return psVar2;
    }
    psVar2 = psVar2 + 10;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return (short *)0x0;
}


// ==== find_pillbox_in_range @ 0001115c ====

undefined8 find_pillbox_in_range(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short *psVar5;
  
  sVar2 = (short)in_D0;
  sVar4 = (short)in_D1;
  sVar3 = sVar2;
  if (sVar4 < sVar2) {
    sVar3 = sVar4;
    sVar4 = sVar2;
  }
  uVar1 = (ushort)pillbox_count;
  psVar5 = pillboxes_ptr;
  while (uVar1 = uVar1 - 1, uVar1 != 0xffff) {
    if (*(char *)(psVar5 + 4) == '\0') {
      sVar2 = *psVar5;
      in_D0 = CONCAT22((short)((uint)in_D0 >> 0x10),sVar2);
      if ((sVar3 <= sVar2) && (sVar2 < sVar4)) goto LAB_000111a0;
    }
    psVar5 = psVar5 + 7;
  }
  in_D0 = 0;
LAB_000111a0:
  return CONCAT44(in_D0,in_D1);
}


// ==== find_ship_gun_in_range @ 000111a6 ====

undefined * find_ship_gun_in_range(void)

{
  short sVar1;
  short in_D0w;
  undefined *puVar2;
  short in_D1w;
  short sVar3;
  short sVar4;
  int iVar5;
  undefined **ppuVar6;
  undefined **ppuVar7;
  
  sVar4 = in_D0w;
  if (in_D1w < in_D0w) {
    sVar4 = in_D1w;
    in_D1w = in_D0w;
  }
  ppuVar6 = &ship_ptr_list;
  do {
    do {
      ppuVar7 = ppuVar6 + 1;
      puVar2 = *ppuVar6;
      if ((int)puVar2 < 0) {
        return (undefined *)0x0;
      }
      ppuVar6 = ppuVar7;
    } while ((*(int *)(puVar2 + 0x12) == 0) || (puVar2[4] == '\0'));
    iVar5 = *(int *)(puVar2 + 6);
    sVar3 = *(short *)(puVar2 + 10);
    while (sVar3 = sVar3 + -1, sVar3 != -1) {
      sVar1 = *(short *)(iVar5 + 4);
      puVar2 = (undefined *)CONCAT22((short)((uint)puVar2 >> 0x10),sVar1);
      if ((sVar4 <= sVar1) && (sVar1 <= in_D1w)) {
        return puVar2;
      }
      iVar5 = iVar5 + 0xe;
    }
  } while( true );
}


// ==== choose_night_flag @ 000111fc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void choose_night_flag(void)

{
  ushort uVar1;
  
  uVar1 = 0;
  if ('\x06' < (char)(&mission_index_table)[(short)(mission_in_rank + rank * 4)]) {
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    uVar1 = (*_thunk_FUN_000203be)();
    uVar1 = uVar1 >> 0xf;
  }
  night_flag = uVar1;
  return;
}


// ==== FUN_00011234 @ 00011234 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011234(void)

{
  (**(code **)(DAT_00026ec4 + -0xc6))();
  (*_thunk_FUN_000134ae)();
  (*_free_sounds)();
  (*_thunk_FUN_00012bbe)();
  FUN_000124e0();
  return;
}


// ==== FUN_00011256 @ 00011256 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011256(void)

{
  (**(code **)(DAT_00026ec4 + -0xc6))();
  (*_thunk_FUN_000134ae)();
  (*_free_sounds)();
  FUN_000124e0();
  return;
}


// ==== snapshot_player_motion @ 00011274 ====

void snapshot_player_motion(void)

{
  DAT_00026db2._0_2_ = player_vspeed;
  DAT_00026db2._2_2_ = 0;
  DAT_00026db6._0_2_ = player_hspeed;
  DAT_00026db6._2_2_ = 0;
  DAT_00026dba._0_2_ = player_x;
  DAT_00026dba._2_2_ = 0;
  DAT_00026dbe = player_y;
  DAT_00026dc0 = 0;
  pitch_binary_angle = (short)(((short)(pitch_smooth * 2) * 0x200) / 18000);
  return;
}


// ==== carrier_menu_input @ 000112b0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void carrier_menu_input(void)

{
  ushort uVar1;
  
  if ((carrier_menu_active != '\0') && (mission_complete == 0)) {
    uVar1 = input_word;
    if (input_word == 0) {
      if (_DAT_00026eae == 0x4d) {
        uVar1 = 2;
      }
      if (_DAT_00026eae == 0x4c) {
        uVar1 = 1;
      }
      if (_DAT_00026eae == 0x44) {
        uVar1 = 0x10;
      }
      if (_DAT_00026eae == 0x43) {
        uVar1 = 0x10;
      }
    }
    if (uVar1 != 0) {
      if ((uVar1 & 0x30) != 0) {
        carrier_menu_active = 0;
        player_state = 0xb;
        carrier_phase = 2;
        return;
      }
      if (weapon_menu_debounce < '\x01') {
        if ((uVar1 & 3) != 0) {
          weapon_menu_debounce = '\x02';
          if ((uVar1 & 1) == 0) {
            weapon_type = weapon_type + 1;
            if (weapon_type == 3) {
              weapon_type = 0;
            }
          }
          else {
            weapon_type = weapon_type + -1;
            if (weapon_type == -1) {
              weapon_type = 2;
            }
          }
          if (ordnance_count != -1) {
            ordnance_count = (&ordnance_per_weapon)[weapon_type];
          }
          (*_hud_set_ammo_drum)();
        }
      }
      else {
        weapon_menu_debounce = weapon_menu_debounce + -1;
      }
    }
  }
  return;
}


// ==== logic_tick @ 00011386 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void logic_tick(void)

{
  bool bVar1;
  short sVar2;
  
  if (paused == '\0') {
    if (player_state == 0) {
      if ((player_oil != 0x80) &&
         (sVar2 = DAT_000272a0 + -1, bVar1 = DAT_000272a0 < 1, DAT_000272a0 = sVar2,
         sVar2 == 0 || bVar1)) {
        DAT_000272a0 = 0x50;
        player_oil = player_oil + -1;
      }
      sVar2 = DAT_0002729e + -1;
      bVar1 = DAT_0002729e < 1;
      DAT_0002729e = sVar2;
      if (sVar2 == 0 || bVar1) {
        player_fuel = player_fuel + -1;
        DAT_0002729e = fuel_interval;
      }
    }
    DAT_00027296 = DAT_00027296 + 1 & 1;
    bob_timer = bob_timer + -1;
    if (bob_timer < 0) {
      bob_timer = DAT_00025338;
      bob_phase = bob_phase + 1 & 7;
      wave_bob = (byte)(&DAT_00024b94)[(short)bob_phase] + 1;
    }
    input_word = pop_input_queue();
    if ((DAT_00026c8e == 0) ||
       (sVar2 = DAT_00026c8e + -1, bVar1 = DAT_00026c8e < 1, DAT_00026c8e = sVar2,
       sVar2 == 0 || bVar1)) {
      carrier_menu_input();
      carrier_phase_tick();
    }
    (*_player_update)();
    (*_update_enemy_planes)();
    sound_update_continuous();
    (*_player_gun_vs_enemy_planes)();
    sound_arbitrate_channels();
    snapshot_player_motion();
    oil_leak_smoke();
    (*_update_projectiles)();
    machine_gun_ground_fire();
    bVar1 = plane_launch_cooldown < 1;
    plane_launch_cooldown = plane_launch_cooldown + -1;
    if (bVar1) {
      plane_launch_cooldown = 0;
    }
    update_airfields();
    update_ship_plane_launch();
    update_sinking_ships();
    update_soldiers_leaving_buildings();
    move_victory_confetti();
  }
  return;
}


// ==== carrier_phase_tick @ 00011460 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void carrier_phase_tick(void)

{
  if ((frame_counter_mod100 != DAT_000272a2) &&
     (DAT_000272a2 = frame_counter_mod100, carrier_phase != 0)) {
    if (carrier_phase == 2) {
      elevator_offset = elevator_offset + -1;
      if (elevator_offset == 0) {
        carrier_phase = 0;
        (*_sound_stop_all)(frame_counter_mod100);
        (*_sfx_metal_clang)();
        (*_engine_sound_start)();
      }
    }
    else if ((carrier_phase == 3) &&
            (elevator_offset = elevator_offset + 1, elevator_offset == 0x20)) {
      (*_sound_stop_all)(frame_counter_mod100);
      (*_sfx_metal_clang)();
      rearm_new_plane();
    }
  }
  return;
}


// ==== run_queued_logic_ticks @ 000114d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void run_queued_logic_ticks(void)

{
  while (demo_tick_budget != 0) {
    (*_wait_next_vbl)();
  }
  if (paused < '\0') {
    return;
  }
  while (0 < input_queue_count) {
    logic_tick();
  }
  demo_tick_budget = 0;
  if (demo_mode != 0) {
    demo_tick_budget = 2;
  }
  return;
}


// ==== update_ship_plane_launch @ 00011510 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_ship_plane_launch(void)

{
  undefined2 *puVar1;
  short *psVar2;
  short sVar3;
  short sVar4;
  short *psVar5;
  undefined **ppuVar6;
  
  if ((DAT_000250e6 != 0) &&
     (sVar4 = (DAT_000250e6 + -1) * 8, 0 < *(short *)(&DAT_000250ee + sVar4))) {
    jcarrier_takeoff_speed = (jcarrier_takeoff_speed + 8) - (jcarrier_takeoff_speed >> 4);
    sVar3 = *(short *)(&DAT_000250f0 + sVar4) - (jcarrier_takeoff_speed >> 4);
    *(short *)(&DAT_000250f0 + sVar4) = sVar3;
    if (sVar3 < (short)(ship_jcarrier << 2)) {
      DAT_000250e6 = DAT_000250e6 + -1;
      (*_spawn_enemy_plane)(*(undefined2 *)(&DAT_000250f0 + sVar4),0xffff);
    }
  }
  if (plane_launch_cooldown == 0) {
    sVar4 = 4;
    psVar5 = (short *)&ship_plane_blocks;
    ppuVar6 = &ship_ptr_list;
    do {
      psVar2 = (short *)*ppuVar6;
      if ((((psVar2[2] != 0) && (psVar2[9] != 0)) && (0 < psVar2[6])) &&
         (((psVar5[2] <= DAT_00026dba._0_2_ && (DAT_00026dba._0_2_ <= psVar5[3])) &&
          ((zeros_airborne < psVar5[1] && (*psVar5 != 0)))))) {
        if (sVar4 == 0) {
          puVar1 = (undefined2 *)((int)psVar5 + (short)((*psVar5 + -1) * 8) + 8);
          *puVar1 = 1;
          jcarrier_takeoff_speed = 0;
          puVar1[1] = *psVar2 * 4 + 0x17c;
          puVar1[2] = 0x21;
          plane_launch_cooldown = 100;
          return;
        }
        *psVar5 = *psVar5 + -1;
        (*_spawn_enemy_plane)(*(undefined2 *)((int)psVar5 + (short)(*psVar5 * 8) + 10),0xffff);
        plane_launch_cooldown = 100;
      }
      psVar5 = psVar5 + 0x20;
      sVar4 = sVar4 + -1;
      ppuVar6 = ppuVar6 + 1;
    } while (sVar4 != -1);
    return;
  }
  return;
}


// ==== update_airfields @ 00011622 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_airfields(void)

{
  ushort uVar1;
  short sVar2;
  short sVar3;
  short *psVar4;
  
  sVar2 = 3;
  psVar4 = &airfield_zones;
  do {
    if (psVar4[4] != 0) {
      uVar1 = psVar4[6] + 1;
      if (0x38 < (short)uVar1) {
        uVar1 = 0x38;
      }
      psVar4[6] = uVar1;
      if (psVar4[7] == -1) {
        psVar4[4] = psVar4[4] - (uVar1 >> 3);
        sVar2 = psVar4[4];
        if (*psVar4 <= sVar2) {
          return;
        }
      }
      else {
        psVar4[4] = (uVar1 >> 3) + psVar4[4];
        sVar2 = psVar4[4];
        if (sVar2 <= psVar4[1]) {
          return;
        }
      }
      (*_spawn_enemy_plane)(sVar2,psVar4[7]);
      psVar4[4] = 0;
      return;
    }
    psVar4 = psVar4 + 10;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  if (plane_launch_cooldown == 0) {
    sVar3 = 3;
    psVar4 = &airfield_zones;
    sVar2 = DAT_00026dba._0_2_;
    do {
      if (((short)(*psVar4 + -0x1e0) <= sVar2) && (sVar2 <= (short)(psVar4[1] + 0x1e0))) {
        if (psVar4[2] <= zeros_airborne) {
          return;
        }
        if (psVar4[3] < 1) {
          return;
        }
        psVar4[3] = psVar4[3] + -1;
        plane_launch_cooldown = 100;
        sVar2 = psVar4[1] + -0x20 + psVar4[3] * -0x40;
        if (psVar4[7] != -1) {
          sVar2 = psVar4[3] * 0x40 + *psVar4 + 0x20;
        }
        psVar4[4] = sVar2;
        psVar4[6] = 0;
        sVar2 = DAT_00026dba._0_2_;
      }
      psVar4 = psVar4 + 10;
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
  }
  return;
}


// ==== pop_input_queue @ 00011714 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pop_input_queue(void)

{
  bool bVar1;
  short sVar2;
  undefined2 *puVar3;
  
  (*_thunk_FUN_00022d48)();
  puVar3 = &input_queue;
  sVar2 = input_queue_count + -1;
  bVar1 = input_queue_count < 1;
  input_queue_count = sVar2;
  if (bVar1) {
    sVar2 = 0;
    input_queue_count = sVar2;
  }
  while (sVar2 = sVar2 + -1, sVar2 != -1) {
    *puVar3 = puVar3[1];
    puVar3 = puVar3 + 1;
  }
  (*_thunk_FUN_00022d66)();
  return;
}


// ==== input_queue_clear @ 0001174a ====

void input_queue_clear(void)

{
  input_queue_count = 0;
  input_queue = 0;
  return;
}


// ==== vbl_server @ 00011754 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 vbl_server(void)

{
  ushort uVar1;
  byte bVar2;
  bool bVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  undefined4 in_D1;
  ushort extraout_D1w;
  short sVar7;
  undefined2 *extraout_A0;
  ushort *puVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  int *in_A1;
  undefined2 *puVar11;
  undefined2 *puVar12;
  
  vbl_flag = 0xff;
  if (paused != '\0') {
    vbl_flag = 0xff;
    return in_D1;
  }
  *in_A1 = *in_A1 + 1;
  if (DAT_000272b4 == 0) {
    (*_fire_button_debounce)();
    sVar6 = vbl_input_divider + -1;
    bVar3 = vbl_input_divider < 1;
    vbl_input_divider = sVar6;
    if (sVar6 == 0 || bVar3) {
      vbl_input_divider = 4;
      if (demo_mode == 1) {
        if ((DAT_00026ca4 == 0) || (demo_tick_budget == 0)) goto LAB_00011842;
        demo_tick_budget = demo_tick_budget + -1;
        bVar2 = *(byte *)(demo_buffer + (short)demo_pos);
        uVar5 = (ushort)bVar2;
        if ((bVar2 == 0xff) || (demo_pos = demo_pos + 1, 0x1385 < demo_pos)) {
          session_over = 0xff;
        }
        input_word = (ushort)bVar2;
      }
      else {
        uVar5 = (*_build_input_word)();
      }
      puVar11 = &input_queue;
      if (input_queue_count < 6) {
        input_queue_count = input_queue_count + 1;
      }
      else {
        uVar5 = pop_input_queue();
        puVar11 = extraout_A0;
        input_queue_count = extraout_D1w;
      }
      *(ushort *)((int)puVar11 + (int)(short)((input_queue_count - 1) * 2)) = input_word;
      if (((demo_mode == 2) && (DAT_00026ca4 != 0)) && (demo_tick_budget != 0)) {
        demo_tick_budget = demo_tick_budget + -1;
        *(undefined1 *)(demo_buffer + (short)demo_pos) = (undefined1)input_word;
        demo_pos = demo_pos + 1;
        input_word = uVar5;
        if (0x1385 < demo_pos) {
          session_over = 0xff;
        }
      }
    }
  }
LAB_00011842:
  if (not_in_game == '\0') {
    game_vbl_timer = game_vbl_timer + 1;
    if (ticker_scroll_count != 0) {
      puVar8 = (ushort *)(ticker_bitmap_ptr + 0x444);
      sVar6 = 0xc;
      ticker_scroll_count = ticker_scroll_count + -1;
      do {
        uVar5 = puVar8[-1];
        puVar8[-1] = uVar5 << 1;
        uVar1 = puVar8[-2];
        puVar8[-2] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-3];
        puVar8[-3] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-4];
        puVar8[-4] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-5];
        puVar8[-5] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-6];
        puVar8[-6] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-7];
        puVar8[-7] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-8];
        puVar8[-8] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-9];
        puVar8[-9] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-10];
        puVar8[-10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xb];
        puVar8[-0xb] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xc];
        puVar8[-0xc] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xd];
        puVar8[-0xd] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xe];
        puVar8[-0xe] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xf];
        puVar8[-0xf] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x10];
        puVar8[-0x10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x11];
        puVar8[-0x11] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x12];
        puVar8[-0x12] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x13];
        puVar8[-0x13] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x14];
        puVar8[-0x14] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x15];
        puVar8[-0x15] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x16];
        puVar8[-0x16] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x17];
        puVar8[-0x17] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x18];
        puVar8[-0x18] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x19];
        puVar8[-0x19] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1a];
        puVar8[-0x1a] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1b];
        puVar8[-0x1b] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1c];
        puVar8[-0x1c] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1d];
        puVar8[-0x1d] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1e];
        puVar8[-0x1e] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1f];
        puVar8[-0x1f] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x20];
        puVar8[-0x20] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x21];
        puVar8[-0x21] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x22];
        puVar8[-0x22] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x23];
        puVar8[-0x23] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x24];
        puVar8[-0x24] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x25];
        puVar8[-0x25] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x26];
        puVar8[-0x26] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x27];
        puVar8[-0x27] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x28];
        puVar8[-0x28] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x29];
        puVar8[-0x29] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        puVar8 = puVar8 + -0x2a;
        *puVar8 = *puVar8 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        sVar6 = sVar6 + -1;
      } while (sVar6 != -1);
      if ((ticker_char_delay != 0) &&
         (ticker_char_delay = ticker_char_delay + -1, ticker_char_delay != 0)) {
        return in_D1;
      }
    }
    if (ticker_message != (char *)0x0) {
      if (*ticker_message == '\0') {
        ticker_message = (char *)0x0;
        ticker_char_delay = 0;
      }
      else {
        ticker_scroll_count = 0x2a0;
        uVar5 = (ushort)(byte)(*ticker_message - font_first_char);
        bVar2 = *(byte *)(ticker_font + 4 + (int)(short)uVar5);
        if (bVar2 == 0) {
          ticker_char_delay = 10;
          ticker_message = ticker_message + 1;
        }
        else {
          ticker_char_delay = bVar2 + 1;
          puVar9 = (undefined2 *)
                   (*(short *)((int)&font_glyph_offsets + (int)(short)(uVar5 * 2)) + font_glyph_data
                   );
          puVar11 = (undefined2 *)(ticker_bitmap_ptr + 0x50);
          sVar6 = font_height;
          ticker_message = ticker_message + 1;
          while (sVar6 = sVar6 + -1, sVar6 != -1) {
            sVar4 = ((ushort)(bVar2 + 0xf) >> 4) - 1;
            puVar10 = puVar9;
            sVar7 = sVar4;
            do {
              puVar12 = puVar11;
              puVar9 = puVar10 + 1;
              *puVar12 = *puVar10;
              sVar7 = sVar7 + -1;
              puVar10 = puVar9;
              puVar11 = puVar12 + 1;
            } while (sVar7 != -1);
            puVar11 = (undefined2 *)((int)puVar12 + (0x54 - (short)(sVar4 * 2)));
          }
        }
      }
    }
  }
  return in_D1;
}


// ==== machine_gun_ground_fire @ 000119bc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void machine_gun_ground_fire(void)

{
  undefined2 uVar1;
  undefined1 uVar2;
  short sVar3;
  undefined2 *extraout_A0;
  int extraout_A0_00;
  int iVar4;
  
  if ((((gun_firing != 0) && (DAT_00026db2._0_2_ < 0)) && (player_y < 0xa0)) &&
     (sVar3 = 0x13, iVar4 = gun_impacts_ptr, landing_attitude == 0)) {
    do {
      if (*(char *)(iVar4 + 2) == '\0') {
        gun_ground_impact_x();
        uVar1 = kill_soldiers_near();
        *extraout_A0 = uVar1;
        (*_add_gun_impact)();
        uVar2 = (*_map_cell_at_x)();
        *(undefined1 *)(extraout_A0_00 + 3) = uVar2;
        return;
      }
      iVar4 = iVar4 + 4;
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
  }
  return;
}


// ==== FUN_00011a14 @ 00011a14 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011a14(void)

{
  undefined2 uVar1;
  short in_D0w;
  undefined1 uVar2;
  short sVar3;
  short *psVar4;
  undefined2 *extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  
  psVar4 = DAT_00026df4;
  if ((*(char *)(DAT_00026df4 + 1) == '\0') && (*DAT_00026df4 = in_D0w, in_D0w != 0)) {
    uVar2 = (*_map_cell_at_x)();
    *(undefined1 *)(extraout_A0_01 + 3) = uVar2;
    *(undefined1 *)(extraout_A0_01 + 2) = 4;
    return;
  }
  sVar3 = 0x12;
  do {
    if (*(char *)(psVar4 + 3) == '\0') {
      gun_ground_impact_x();
      uVar1 = kill_soldiers_near();
      *extraout_A0 = uVar1;
      (*_add_gun_impact)();
      uVar2 = (*_map_cell_at_x)();
      *(undefined1 *)(extraout_A0_00 + 3) = uVar2;
      return;
    }
    sVar3 = sVar3 + -1;
    psVar4 = psVar4 + 2;
  } while (sVar3 != -1);
  return;
}


// ==== FUN_00011a42 @ 00011a42 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00011a42(short param_1)

{
  undefined4 uVar1;
  undefined4 in_D1;
  short sVar2;
  undefined8 uVar3;
  
  if (param_1 < 0) {
    uVar3 = (*_tan_lookup)();
    sVar2 = (short)((uint)uVar3 / ((uint)((ulonglong)uVar3 >> 0x20) & 0xffff));
    if (-1 < player_dir) {
      sVar2 = -sVar2;
    }
    uVar1 = CONCAT22((short)((ulonglong)uVar3 >> 0x30),render_player_x - sVar2);
  }
  else {
    uVar1 = 0;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== gun_ground_impact_x @ 00011a46 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 gun_ground_impact_x(void)

{
  short in_D0w;
  undefined4 uVar1;
  undefined4 in_D1;
  short sVar2;
  undefined8 uVar3;
  
  if (in_D0w < 0) {
    uVar3 = (*_tan_lookup)();
    sVar2 = (short)((uint)uVar3 / ((uint)((ulonglong)uVar3 >> 0x20) & 0xffff));
    if (-1 < player_dir) {
      sVar2 = -sVar2;
    }
    uVar1 = CONCAT22((short)((ulonglong)uVar3 >> 0x30),render_player_x - sVar2);
  }
  else {
    uVar1 = 0;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== FUN_00011a84 @ 00011a84 ====

undefined8 FUN_00011a84(undefined4 param_1)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  short *extraout_A0;
  short *psVar2;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)CONCAT24(param_1._0_2_ - param_1._2_2_,(uint)(ushort)(param_1._2_2_ * 2));
  psVar2 = soldiers_ptr;
  sVar1 = soldier_slot_count;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if ((psVar2[3] == 1) && ((ushort)(*psVar2 - (short)(uVar3 >> 0x20)) <= (ushort)uVar3)) {
      psVar2[3] = 2;
      *(undefined1 *)((int)psVar2 + 3) = 5;
      *(undefined1 *)(psVar2 + 2) = 2;
      uVar3 = sfx_scream();
      psVar2 = extraout_A0;
    }
    psVar2 = psVar2 + 4;
  }
  destroy_torpedoes_near();
  return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),param_1._0_2_),
                  CONCAT22((short)((uint)in_D1 >> 0x10),param_1._2_2_));
}


// ==== kill_soldiers_near @ 00011a8c ====

undefined8 kill_soldiers_near(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  short *extraout_A0;
  short *psVar2;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)CONCAT24((short)in_D0 - (short)in_D1,(uint)(ushort)((short)in_D1 * 2));
  psVar2 = soldiers_ptr;
  sVar1 = soldier_slot_count;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if ((psVar2[3] == 1) && ((ushort)(*psVar2 - (short)(uVar3 >> 0x20)) <= (ushort)uVar3)) {
      psVar2[3] = 2;
      *(undefined1 *)((int)psVar2 + 3) = 5;
      *(undefined1 *)(psVar2 + 2) = 2;
      uVar3 = sfx_scream();
      psVar2 = extraout_A0;
    }
    psVar2 = psVar2 + 4;
  }
  destroy_torpedoes_near();
  return CONCAT44(in_D0,in_D1);
}


// ==== destroy_torpedoes_near @ 00011ae2 ====

undefined8 destroy_torpedoes_near(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar1;
  short sVar2;
  undefined2 *puVar3;
  
  puVar3 = &projectiles;
  sVar2 = 0xe;
  do {
    if ((*(char *)(puVar3 + 6) != '\0') && (puVar3[0x11] == 2)) {
      uVar1 = puVar3[4] - (short)in_D0;
      if ((short)uVar1 < 0) {
        uVar1 = -uVar1;
      }
      if (uVar1 <= (ushort)in_D1) {
        *(undefined1 *)(puVar3 + 0x10) = 8;
        *(undefined1 *)((int)puVar3 + 0x21) = 1;
      }
    }
    puVar3 = puVar3 + 0x15;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  if (DAT_000254f0._0_1_ != '\0') {
    uVar1 = DAT_000254ec - (short)in_D0;
    if ((short)uVar1 < 0) {
      uVar1 = -uVar1;
    }
    if (uVar1 <= (ushort)in_D1) {
      DAT_00025504._0_1_ = 8;
      DAT_00025504._1_1_ = 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== oil_leak_smoke @ 00011bfc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void oil_leak_smoke(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort in_D1w;
  
  if ((((DAT_00027296 != 0) && (player_state != 6)) && (player_state != 8)) &&
     (uVar2 = 0x80 - player_oil, uVar2 != 0)) {
    if (uVar2 < 0x14) {
      uVar2 = uVar2 * 8 & 0xf0;
      uVar1 = (*_thunk_FUN_000203be)();
      in_D1w = uVar2 + (uVar1 & 0xf);
      uVar2 = in_D1w >> 3;
      if (((&DAT_0002551a)[(short)uVar2] & '\x01' << (in_D1w & 7)) == 0) {
        return;
      }
    }
    spawn_player_smoke(uVar2,in_D1w);
  }
  return;
}


// ==== move_victory_confetti @ 00011c5e ====

void move_victory_confetti(void)

{
  int *piVar1;
  int *piVar2;
  
  if (victory_balloons != '\0') {
    piVar1 = confetti_particles_ptr + 0x5a;
    piVar2 = confetti_particles_ptr;
    do {
      if (*(char *)((int)piVar2 + 0x11) != '\0') {
        *piVar2 = piVar2[2] + *piVar2;
        piVar2[1] = piVar2[3] + piVar2[1];
        if (0xa9 < *(short *)(piVar2 + 1)) {
          *(undefined1 *)((int)piVar2 + 0x11) = 0;
        }
      }
      piVar2 = (int *)((int)piVar2 + 0x12);
    } while ((int)piVar2 < (int)piVar1);
  }
  return;
}


// ==== update_sinking_ships @ 00011cae ====

undefined4 update_sinking_ships(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined **ppuVar2;
  undefined **extraout_A0;
  undefined **ppuVar3;
  
  sVar1 = 4;
  ppuVar2 = &ship_ptr_list;
  do {
    ppuVar3 = ppuVar2 + 1;
    if ((*(short *)(*ppuVar2 + 4) != 0) && (*(short *)(*ppuVar2 + 0xc) == 0)) {
      sVar1 = ship_sink_step();
      ppuVar3 = extraout_A0;
    }
    sVar1 = sVar1 + -1;
    ppuVar2 = ppuVar3;
  } while (sVar1 != -1);
  return in_D0;
}


// ==== ship_sink_step @ 00011cd8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 ship_sink_step(void)

{
  short sVar1;
  short sVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar3;
  short *in_A1;
  undefined2 *puVar4;
  bool bVar5;
  
  sVar1 = in_A1[0xb];
  sVar2 = sVar1 + -1;
  in_A1[0xb] = sVar2;
  if (sVar2 != 0 && 0 < sVar1) goto LAB_00011dde;
  in_A1[10] = in_A1[10] + 1;
  in_A1[0xb] = in_A1[0xc];
  if (in_A1[0xc] != 0) {
    in_A1[0xc] = in_A1[0xc] + -1;
  }
  if (in_A1[9] == 0) {
    if (carrier_phase == 1) {
      player_state = 0xb;
      carrier_phase = 2;
      carrier_menu_active = 0;
      turn_frame = 0;
    }
  }
  else if (in_A1[10] == 10) {
    score = in_A1[9] + score;
    show_ship_sunk_message();
    bVar5 = SBORROW1(ships_remaining,'\x01');
    ships_remaining = ships_remaining - 1;
    if ((ships_remaining == 0 || bVar5 != (short)((ushort)ships_remaining << 8) < 0) &&
       (enemy_islands_remaining == '\0')) {
      (*_advance_mission)();
    }
    else {
      (*_ticker_start_message)();
    }
    goto LAB_00011dde;
  }
  if (in_A1[9] == 0) {
    if (in_A1[10] < 0x21) goto LAB_00011dde;
    if ((in_A1[10] < 0x22) && (player_state == 1)) {
      player_state = 6;
      player_y = 0;
      lives = 0;
      carrier_menu_active = 0;
      game_over_countdown = 100;
    }
    if (in_A1[10] < 0x78) goto LAB_00011dde;
    in_A1[2] = 0;
    DAT_00025511 = 0xff;
  }
  else {
    if (in_A1[10] < 0x78) goto LAB_00011dde;
    ships_present = ships_present + -1;
    in_A1[6] = -1;
  }
  uVar3 = (ushort)-(*in_A1 - in_A1[1]) >> 1;
  puVar4 = (undefined2 *)(DAT_00024578 + *in_A1);
  do {
    *puVar4 = 0;
    uVar3 = uVar3 - 1;
    puVar4 = puVar4 + 1;
  } while (uVar3 != 0xffff);
LAB_00011dde:
  return CONCAT44(in_D0,in_D1);
}


// ==== update_soldiers_leaving_buildings @ 00011de4 ====

undefined8 update_soldiers_leaving_buildings(void)

{
  char cVar1;
  undefined4 in_D0;
  byte bVar2;
  undefined4 in_D1;
  ushort uVar3;
  int extraout_A0;
  int extraout_A0_00;
  int iVar4;
  
  uVar3 = (ushort)bunker_count;
  iVar4 = bunkers_ptr;
  while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
    if ((*(char *)(iVar4 + 0xb) != '\0') &&
       (cVar1 = *(char *)(iVar4 + 0xb) + -1, *(char *)(iVar4 + 0xb) = cVar1, cVar1 == '\0')) {
      spawn_soldier();
      cVar1 = *(char *)(extraout_A0 + 10) + -1;
      *(char *)(extraout_A0 + 10) = cVar1;
      iVar4 = extraout_A0;
      if (cVar1 != '\0') {
        bVar2 = (byte)(vbl_counter >> 4) & 0x1f;
        if ((vbl_counter >> 4 & 0x1f) == 0) {
          bVar2 = 3;
        }
        *(byte *)(extraout_A0 + 0xb) = bVar2;
      }
    }
    iVar4 = iVar4 + 0x10;
  }
  uVar3 = (ushort)hut_count;
  iVar4 = huts_ptr;
  while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
    if ((*(char *)(iVar4 + 0xb) != '\0') &&
       (cVar1 = *(char *)(iVar4 + 0xb) + -1, *(char *)(iVar4 + 0xb) = cVar1, cVar1 == '\0')) {
      spawn_soldier();
      cVar1 = *(char *)(extraout_A0_00 + 10) + -1;
      *(char *)(extraout_A0_00 + 10) = cVar1;
      iVar4 = extraout_A0_00;
      if (cVar1 != '\0') {
        bVar2 = (byte)(vbl_counter >> 4) & 0x1f;
        if ((vbl_counter >> 4 & 0x1f) == 0) {
          bVar2 = 3;
        }
        *(byte *)(extraout_A0_00 + 0xb) = bVar2;
      }
    }
    iVar4 = iVar4 + 0x10;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== spawn_soldier @ 00011e82 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 spawn_soldier(void)

{
  undefined4 in_D0;
  ushort uVar1;
  undefined4 in_D1;
  byte bVar2;
  short sVar3;
  undefined4 *in_A0;
  short *psVar4;
  
  bVar2 = (byte)in_D1;
  if ((char)in_D0 != '\x01') {
    if ((char)in_D0 != '\x02') goto LAB_00011f48;
    sVar3 = (ushort)*(byte *)((int)in_A0 + 9) << 2;
    bVar2 = 1;
    if (((short)*in_A0 != *(short *)((int)&island_bunker_range + (int)sVar3)) &&
       (bVar2 = 0xff, (short)*in_A0 != *(short *)((int)&island_bunker_range + sVar3 + 2))) {
      bVar2 = 0;
    }
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    uVar1 = (*_thunk_FUN_000203be)();
    if ((uVar1 & 0xf) == 0 && -1 < (short)uVar1) {
      bVar2 = -bVar2;
    }
  }
  psVar4 = soldiers_ptr;
  if (soldier_slot_count != 0) {
    for (; psVar4[3] != 0; psVar4 = psVar4 + 4) {
    }
    psVar4[3] = 1;
    sVar3 = *(short *)(in_A0 + 1);
    *(undefined1 *)((int)psVar4 + 5) = *(undefined1 *)((int)in_A0 + 9);
    if (bVar2 == 0) {
      bVar2 = (byte)vbl_counter;
    }
    *(byte *)(psVar4 + 1) = bVar2;
    if (-1 < (char)bVar2) {
      sVar3 = *(short *)((int)in_A0 + 6);
    }
    *psVar4 = sVar3;
    *(byte *)((int)psVar4 + 3) = bVar2 & 7;
    *(byte *)((int)psVar4 + 3) = *(byte *)((int)psVar4 + 3) & 3;
    *psVar4 = (ushort)(bVar2 & 7) * 4 + *psVar4;
  }
LAB_00011f48:
  return CONCAT44(in_D0,in_D1);
}


// ==== sound_stop_all @ 00011f4e ====

void sound_stop_all(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  puVar2 = &sound_slots;
  sVar1 = 7;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 0xc;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  sound_arbitrate_channels();
  return;
}


// ==== sound_slots_clear @ 00011f64 ====

void sound_slots_clear(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  puVar2 = &sound_slots;
  sVar1 = 7;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 0xc;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}


// ==== init_sound_slots @ 00011f76 ====

void init_sound_slots(void)

{
  DAT_000272ba = snd_machinegun;
  DAT_000272be = DAT_000254c2;
  DAT_000272c2 = 200;
  DAT_000272c4 = 0x40;
  DAT_000272c6 = 0xffff;
  sound_slots = 0;
  DAT_000272d2 = snd_engine;
  DAT_000272d6 = DAT_000254ca;
  DAT_000272da = 0x17c;
  DAT_000272dc = 0x3e;
  DAT_000272de = 0xffff;
  DAT_000272d0 = 0;
  DAT_000272ea = snd_machinegun;
  DAT_000272ee = DAT_000254c2;
  DAT_000272f2 = 0xa0;
  DAT_000272f4 = 0x39;
  DAT_000272f6 = 0xffff;
  DAT_000272e8 = 0;
  DAT_00027302 = snd_engine;
  DAT_00027306 = DAT_000254ca;
  DAT_0002730a = 0x14a;
  DAT_0002730c = 0x40;
  DAT_0002730e = 0xffff;
  DAT_00027300 = 0;
  DAT_0002731a = snd_boom;
  DAT_0002731e = DAT_000254c6;
  DAT_00027322 = 500;
  DAT_00027324 = 0x40;
  DAT_00027326 = 1;
  DAT_00027318 = 0;
  DAT_00027332 = snd_splash;
  DAT_00027336 = DAT_000254ce;
  DAT_0002733a = 0x15e;
  DAT_0002733c = 0x40;
  DAT_0002733e = 1;
  DAT_00027330 = 0;
  DAT_0002734a = snd_machinegun;
  DAT_0002734e = DAT_000254c2;
  DAT_00027352 = 0x140;
  DAT_00027354 = 0x40;
  DAT_00027356 = 0xffff;
  DAT_00027348 = 0;
  return;
}


// ==== sound_arbitrate_channels @ 00012066 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sound_arbitrate_channels(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short *psVar8;
  short *psVar9;
  
  sVar6 = 3;
  sVar7 = 0;
  psVar8 = &sound_slots;
  do {
    if (((paused == '\0') && (sound_off == '\0')) &&
       (((*(int *)(psVar8 + 1) != 0 && (psVar9 = psVar8, *psVar8 != 0)) ||
        ((psVar9 = psVar8 + 0xc, *(int *)(psVar8 + 0xd) != 0 && (*psVar9 != 0)))))) {
      if (*(int *)(psVar9 + 1) == *(int *)(psVar8 + 8)) {
        if (*(int *)(psVar9 + 5) != *(int *)(psVar8 + 10)) {
          *(int *)(psVar8 + 10) = *(int *)(psVar9 + 5);
          (*_sfx_set_period_volume)();
        }
      }
      else {
        uVar1 = *(undefined4 *)(psVar9 + 1);
        uVar2 = *(undefined4 *)(psVar9 + 3);
        sVar3 = psVar9[5];
        sVar4 = psVar9[6];
        sVar5 = psVar9[7];
        *(undefined4 *)(psVar8 + 8) = uVar1;
        *(undefined4 *)(psVar8 + 10) = *(undefined4 *)(psVar9 + 5);
        (*_sfx_start_channel)(uVar2,sVar7,(int)sVar3,(int)sVar4,(int)sVar5,uVar1);
        (*_sfx_start_channel)();
        (*_sfx_start_channel)();
      }
    }
    else if (*(int *)(psVar8 + 8) != 0) {
      (*_sfx_stop_channel)();
      (*_sfx_stop_channel)();
      (*_sfx_stop_channel)();
      psVar8[8] = 0;
      psVar8[9] = 0;
    }
    sVar7 = sVar7 + 1;
    psVar8 = psVar8 + 0x18;
    sVar6 = sVar6 + -1;
  } while (sVar6 != -1);
  return;
}


// ==== sound_update_continuous @ 00012132 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sound_update_continuous(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  short *psVar7;
  bool bVar8;
  
  if (paused != '\0') {
    return;
  }
  if (sound_off != '\0') {
    return;
  }
  DAT_000272d0 = 0;
  if (engine_volume_target != engine_volume) {
    if (engine_volume_target < engine_volume) {
      engine_volume = engine_volume - 2;
      if (engine_volume < engine_volume_target) {
        engine_volume = engine_volume_target;
      }
    }
    else {
      engine_volume = engine_volume + 1;
    }
  }
  if (engine_volume != 0) {
    DAT_000272d0 = 0xff00;
    uVar5 = (player_y >> 4) + engine_period_base + (pitch_cmd >> 7);
    DAT_000272da = engine_period;
    if (uVar5 != engine_period) {
      if (uVar5 < engine_period) {
        engine_period = engine_period - 10;
        DAT_000272da = engine_period;
        if (engine_period < uVar5) {
          engine_period = uVar5;
          DAT_000272da = uVar5;
        }
      }
      else {
        engine_period = engine_period + 0x14;
        DAT_000272da = engine_period;
        if (uVar5 <= engine_period) {
          engine_period = uVar5;
          DAT_000272da = uVar5;
        }
      }
    }
  }
  sound_slots = gun_firing;
  psVar7 = &enemy_planes;
  sVar1 = 3;
  uVar6 = 0xffff;
  uVar5 = 0;
  do {
    if ((*psVar7 != 0) && (*psVar7 < 3)) {
      sVar3 = psVar7[0x10] - player_x;
      if (sVar3 < 0) {
        sVar3 = -sVar3;
      }
      sVar4 = psVar7[0x13] - player_y;
      if (sVar4 < 0) {
        sVar4 = -sVar4;
      }
      if ((ushort)(sVar4 + sVar3) < uVar6) {
        uVar6 = sVar4 + sVar3;
      }
      uVar5 = psVar7[9] | uVar5;
    }
    psVar7 = psVar7 + 0x1a;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00027300 = 0;
  bVar8 = true;
  DAT_000272dc = engine_volume;
  uVar2 = enemy_engine_volume();
  if (!bVar8) {
    DAT_00027300 = CONCAT11(0xff,(undefined1)DAT_00027300);
    DAT_0002730c = uVar2;
  }
  if ((carrier_phase == 2) || (carrier_phase == 3)) {
    DAT_00027362 = snd_grind;
    DAT_00027366 = DAT_000254de;
    DAT_0002736a = 0x1c2;
    DAT_0002736c = 0x40;
    DAT_0002736e = 0xffff;
    _DAT_00027360 = CONCAT11(0xff,DAT_00027360_1);
    DAT_00027330 = 0;
  }
  else if (carrier_phase == 1) {
    DAT_0002733a = 800;
    DAT_0002733c = 0x22;
    DAT_0002733e = 0xffff;
    DAT_00027330 = CONCAT11(0xff,(undefined1)DAT_00027330);
    goto LAB_000122b4;
  }
  DAT_0002733a = 0x15e;
  DAT_0002733e = 1;
LAB_000122b4:
  if (_aa_gun_sound != 0) {
    _DAT_00027360 = 0;
  }
  DAT_00027354 = aa_gun_volume;
  DAT_00027348 = _aa_gun_sound;
  DAT_00027336 = DAT_000254ce;
  DAT_00027332 = snd_splash;
  DAT_000272e8 = uVar5;
  return;
}


// ==== enemy_engine_volume @ 000122ce ====

short enemy_engine_volume(void)

{
  ushort in_D0w;
  ushort uVar1;
  short sVar2;
  
  uVar1 = in_D0w >> 4;
  if (uVar1 < 0x2d) {
    if (uVar1 < 6) {
      sVar2 = uVar1 << 2;
    }
    else {
      sVar2 = uVar1 + 0x14;
    }
    return 0x40 - sVar2;
  }
  return 0;
}


// ==== volume_from_distance @ 000122f6 ====

short volume_from_distance(void)

{
  ushort in_D0w;
  
  if (in_D0w >> 5 < 0x41) {
    return 0x40 - (in_D0w >> 5);
  }
  return 0;
}


// ==== volume_from_player_distance @ 00012306 ====

void volume_from_player_distance(void)

{
  volume_from_distance();
  return;
}


// ==== sfx_boom @ 00012324 ====

void sfx_boom(void)

{
  if (snd_boom != 0) {
    DAT_00027318._0_1_ = 0xff;
    DAT_00027328 = 0;
    DAT_00027324 = volume_from_player_distance();
  }
  return;
}


// ==== sfx_splash @ 0001233e ====

void sfx_splash(void)

{
  DAT_00027318 = 0;
  DAT_00027330._0_1_ = 0xff;
  DAT_00027328 = 0;
  DAT_0002733c = volume_from_player_distance();
  return;
}


// ==== sfx_metal_clang @ 00012354 ====

void sfx_metal_clang(void)

{
  DAT_00027362 = snd_metal_clang;
  DAT_00027366._2_2_ = 0x1646;
  DAT_0002736a = 0x1c2;
  DAT_0002736c = 0x40;
  DAT_0002736e = 1;
  DAT_00027348 = 0;
  DAT_00027360 = 0xff;
  DAT_00027358 = 0;
  return;
}


// ==== sfx_screech @ 00012380 ====

void sfx_screech(void)

{
  DAT_00027362 = snd_screech;
  DAT_00027366._2_2_ = 0x1a5a;
  DAT_0002736a = 0x15e;
  DAT_0002736c = 0x40;
  DAT_0002736e = 1;
  DAT_00027348 = 0;
  DAT_00027360 = 0xff;
  DAT_00027358 = 0;
  return;
}


// ==== sfx_scream @ 000123ac ====

void sfx_scream(void)

{
  ushort uVar1;
  
  DAT_00027362 = snd_scream;
  DAT_00027366._2_2_ = 0x19ac;
  DAT_0002736a = 0x17c;
  uVar1 = volume_from_player_distance();
  DAT_0002736c = uVar1 >> 1;
  DAT_0002736e = 1;
  DAT_00027348 = 0;
  DAT_00027360 = 0xff;
  DAT_00027358 = 0;
  return;
}


// ==== music_play_song @ 000123dc ====

void music_play_song(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  short sVar3;
  code *pcVar2;
  undefined4 extraout_A0;
  
  pcVar2 = songplay_entry;
  song_number = param_2;
  if ((song_seglist == 0) || ((*songplay_entry)(), sound_off != '\0')) {
    iVar1 = DAT_00026e6e;
    song_seglist = (**(code **)(DAT_00026e6e + -0x96))();
    if (song_seglist == 0) {
      return;
    }
    (*(code *)CONCAT22((short)((uint)(song_seglist << 2) >> 0x10),(short)(song_seglist << 2) + 4))()
    ;
    song_table = extraout_A0;
    songplay_seglist = (**(code **)(iVar1 + -0x96))();
    pcVar2 = (code *)CONCAT22((short)((uint)(songplay_seglist << 2) >> 0x10),
                              (short)(songplay_seglist << 2) + 4);
    songplay_entry = pcVar2;
    (*pcVar2)();
  }
  else {
    do {
      sVar3 = (*pcVar2)();
    } while (sVar3 != 0);
  }
  (*pcVar2)();
  if (sound_off == '\0') {
    (*pcVar2)();
    music_playing._0_1_ = 0xff;
  }
  return;
}


// ==== music_stop_unload @ 00012470 ====

void music_stop_unload(void)

{
  code *pcVar1;
  int iVar2;
  short sVar3;
  
  pcVar1 = songplay_entry;
  if (song_seglist != 0) {
    (*songplay_entry)();
    music_playing = 0;
    if (sound_off == '\0') {
      do {
        sVar3 = (*pcVar1)();
      } while (sVar3 != 0);
    }
    (*pcVar1)();
    iVar2 = DAT_00026e6e;
    (**(code **)(DAT_00026e6e + -0x9c))();
    (**(code **)(iVar2 + -0x9c))();
    song_seglist = 0;
    song_table = 0;
    songplay_seglist = 0;
    songplay_entry = (code *)0x0;
  }
  return;
}


// ==== FUN_000124d8 @ 000124d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000124d8(void)

{
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_000124dc @ 000124dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000124dc(int *param_1)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    (*_thunk_FUN_0002090a)(*param_1);
  }
  *param_1 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000124e0 @ 000124e0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000124e0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int *in_A0;
  
  if ((in_A0 != (int *)0x0) && (*in_A0 != 0)) {
    (*_thunk_FUN_0002090a)(*in_A0);
  }
  *in_A0 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00012502 @ 00012502 ====

void FUN_00012502(void)

{
  int in_A0;
  int in_A1;
  int extraout_A1;
  
  if (in_A0 != 0) {
    FUN_000124e0();
    in_A1 = extraout_A1;
  }
  if (in_A1 != 0) {
    FUN_000124e0();
  }
  return;
}


// ==== init_ship_plane_block @ 0001252c ====

undefined8 init_ship_plane_block(void)

{
  byte bVar1;
  undefined1 uVar2;
  undefined4 in_D0;
  short sVar3;
  undefined4 in_D1;
  short sVar4;
  int in_A0;
  ushort *in_A1;
  ushort *unaff_A2;
  ushort *puVar5;
  ushort *puVar6;
  
  sVar4 = mission_in_rank + rank * 4;
  sVar4 = CONCAT11((char)((ushort)sVar4 >> 8),(&mission_index_table)[sVar4]) * 2;
  bVar1 = *(byte *)(in_A0 + sVar4);
  uVar2 = *(undefined1 *)(in_A0 + 1 + (int)sVar4);
  sVar3 = (short)in_D0 * 4;
  *unaff_A2 = (ushort)bVar1;
  puVar5 = unaff_A2 + 2;
  unaff_A2[1] = CONCAT11((char)((ushort)sVar4 >> 8),uVar2);
  *puVar5 = *in_A1;
  puVar6 = unaff_A2 + 3;
  *puVar5 = sVar3 + *puVar5;
  *puVar6 = in_A1[1];
  *puVar6 = sVar3 + *puVar6;
  sVar4 = bVar1 - 1;
  do {
    puVar5 = in_A1 + 3;
    puVar6 = unaff_A2 + 5;
    unaff_A2[4] = in_A1[2];
    in_A1 = in_A1 + 4;
    *puVar6 = *puVar5;
    *puVar6 = sVar3 + *puVar6;
    *(undefined4 *)(unaff_A2 + 6) = *(undefined4 *)in_A1;
    sVar4 = sVar4 + -1;
    unaff_A2 = unaff_A2 + 4;
  } while (sVar4 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== open_libraries_and_sound @ 00012570 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void open_libraries_and_sound(void)

{
  int iVar1;
  
  iVar1 = DAT_00026ec4;
  DAT_00026e76 = (**(code **)(DAT_00026ec4 + -0x228))();
  if (DAT_00026e76 != 0) {
    DAT_00026e72 = (**(code **)(iVar1 + -0x228))();
    if (DAT_00026e72 != 0) {
      (*_sfx_init)();
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_0001259e @ 0001259e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001259e(void)

{
  int iVar1;
  
  iVar1 = DAT_00026ec4;
  if (DAT_00026e72 != 0) {
    (**(code **)(DAT_00026ec4 + -0x19e))();
  }
  if (DAT_00026e76 != 0) {
    (**(code **)(iVar1 + -0x19e))();
  }
  (*_sfx_shutdown)();
  return;
}


// ==== FUN_000125c6 @ 000125c6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000125c6(void)

{
  int iVar1;
  
  iVar1 = (**(code **)(_DAT_00000004 + -0x126))();
  DAT_0002739c = *(undefined4 *)(iVar1 + 0xb8);
  DAT_00027390 = iVar1;
  *(undefined4 *)(iVar1 + 0xb8) = 0xffffffff;
  DAT_00027394 = *(int **)(iVar1 + 0x32);
  DAT_00027398 = *(undefined4 *)(iVar1 + 0x2e);
  DAT_0002738e = (**(code **)(DAT_00026ec4 + -300))();
  custom_base = 0xdff000;
  DAT_000273a0 = 0;
  DAT_00026eb0 = 0;
  if (*DAT_00027394 == 0x48e7fffe) {
    *(undefined **)(DAT_00027390 + 0x32) = &DAT_00012640;
  }
  else {
    DAT_000270b2 = 0x10;
    DAT_000273a0 = 1;
    DAT_00026eb0 = 1;
  }
  return;
}


// ==== FUN_0001276c @ 0001276c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001276c(void)

{
  int iVar1;
  
  iVar1 = DAT_00027390;
  *(undefined4 *)(DAT_00027390 + 0xb8) = DAT_0002739c;
  *(undefined4 *)(iVar1 + 0x32) = DAT_00027394;
  *(undefined4 *)(iVar1 + 0x2e) = DAT_00027398;
  (**(code **)(_DAT_00000004 + -300))();
  return 0;
}


// ==== load_ticker_font @ 00012794 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 load_ticker_font(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  short sVar2;
  byte *pbVar3;
  short *psVar4;
  undefined8 uVar5;
  
  ticker_font = (short *)(*_thunk_FUN_0001feb4)(s_newarmyfont_000235fc);
  if (ticker_font != (short *)0x0) {
    font_height = *ticker_font;
    font_first_char = *(char *)(ticker_font + 1);
    DAT_00026ebf = *(char *)((int)ticker_font + 3);
    font_glyph_data =
         (byte *)((int)(ticker_font + 2) +
                 (int)(short)((byte)((DAT_00026ebf + '\x01') - font_first_char) + 1 & 0xfffe));
    sVar1 = 0x5f;
    sVar2 = 0;
    pbVar3 = (byte *)(ticker_font + 2);
    psVar4 = &font_glyph_offsets;
    do {
      *psVar4 = sVar2;
      sVar2 = ((ushort)(*pbVar3 + 0xf) >> 4) * 2 * font_height + sVar2;
      sVar1 = sVar1 + -1;
      pbVar3 = pbVar3 + 1;
      psVar4 = psVar4 + 1;
    } while (sVar1 != -1);
    return CONCAT44(in_D0,in_D1);
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar5 = (*_thunk_FUN_0001020e)();
  return uVar5;
}


// ==== FUN_000127f6 @ 000127f6 ====

void FUN_000127f6(void)

{
  FUN_000124e0();
  return;
}


// ==== FUN_0001283e @ 0001283e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001283e(void)

{
  DAT_00026df4 = alloc_mem();
  if (DAT_00026df4 != 0) {
    gun_impacts_ptr = alloc_mem();
    if (gun_impacts_ptr != 0) {
      smoke_particles_ptr = alloc_mem();
      if (smoke_particles_ptr != 0) {
        confetti_particles_ptr = alloc_mem();
        if (confetti_particles_ptr != 0) {
          mask_buffer_size = 0x410;
          mask_buffer = FUN_000158fe();
          if (mask_buffer != 0) {
            cell_frames = alloc_mem();
            if (cell_frames != 0) {
              cell_frames_eighth = alloc_mem();
              if (cell_frames_eighth != 0) {
                return;
              }
            }
          }
        }
      }
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000124d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_000128d6 @ 000128d6 ====

void FUN_000128d6(void)

{
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  return;
}


// ==== install_vbl_server @ 00012910 ====

void install_vbl_server(void)

{
  int iVar1;
  int unaff_A6;
  
  iVar1 = alloc_mem();
  DAT_00026dda = iVar1;
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 8) = 2;
    *(char **)(iVar1 + 10) = s_Interrupt_Server_00023616;
    *(undefined1 *)(iVar1 + 9) = 0xf6;
    *(undefined4 **)(iVar1 + 0xe) = &vbl_counter;
    *(code **)(iVar1 + 0x12) = vbl_server;
    (**(code **)(unaff_A6 + -0xa8))();
    return;
  }
  FUN_000124d8();
  return;
}


// ==== FUN_0001295a @ 0001295a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001295a(void)

{
  undefined4 uVar1;
  
  if (DAT_00026dda == 0) {
    (*_thunk_FUN_0001556e)(s_No_Interrupt_handler_detected__0001297e);
    uVar1 = 0;
  }
  else {
    (**(code **)(DAT_00026ec4 + -0xae))();
    uVar1 = FUN_000124e0();
  }
  return uVar1;
}


// ==== FUN_000129c8 @ 000129c8 ====

undefined8 FUN_000129c8(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_000165c4(s_In_init_asm_000129ba);
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000129dc @ 000129dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000129dc(void)

{
  undefined4 uVar1;
  int iVar2;
  short sVar3;
  int extraout_A0;
  uint extraout_A0_00;
  uint extraout_A0_01;
  uint uVar4;
  int extraout_A0_02;
  int extraout_A0_03;
  ushort uVar5;
  
  uVar1 = (*_load_shape_bank)();
  DAT_00024582 = extraout_A0;
  if ((extraout_A0 != 0) &&
     (world_frames = uVar1, uVar1 = (*_load_shape_bank)(), DAT_0002458e = extraout_A0_00,
     extraout_A0_00 != 0)) {
    sVar3 = *(short *)(extraout_A0_00 + 4) + -1;
    uVar4 = extraout_A0_00;
    hellcat_frames = uVar1;
    do {
      uVar5 = (ushort)uVar4;
      iVar2 = (*_thunk_FUN_0002050e)(uVar5);
      *(undefined2 *)(iVar2 + 8) = 2;
      uVar4 = (uint)uVar5;
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
    uVar1 = (*_load_shape_bank)();
    DAT_00024592 = extraout_A0_01;
    if (extraout_A0_01 != 0) {
      sVar3 = *(short *)(extraout_A0_01 + 4) + -1;
      uVar4 = extraout_A0_01;
      torpedo_frames = uVar1;
      do {
        uVar5 = (ushort)uVar4;
        iVar2 = (*_thunk_FUN_0002050e)(uVar5);
        *(undefined2 *)(iVar2 + 8) = 2;
        uVar4 = (uint)uVar5;
        sVar3 = sVar3 + -1;
      } while (sVar3 != -1);
      uVar1 = (*_load_shape_bank)();
      DAT_0002459a = extraout_A0_02;
      if (extraout_A0_02 != 0) {
        japplane_frames = uVar1;
        uVar1 = (*_load_shape_bank)();
        DAT_00024586 = extraout_A0_03;
        if (extraout_A0_03 != 0) {
          eighth_frames = uVar1;
          return;
        }
      }
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_00012a92 @ 00012a92 ====

void FUN_00012a92(void)

{
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  return;
}


// ==== load_map @ 00012adc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 load_map(void)

{
  int iVar1;
  int iVar2;
  undefined4 in_D0;
  short sVar4;
  undefined4 uVar3;
  short sVar5;
  short *psVar6;
  
  FUN_00013554();
  _session_over = 0;
  ships_present = 0;
  ships_remaining = 0;
  island_count = 0;
  enemy_island_count = 0;
  enemy_islands_remaining = 0;
  sVar4 = 0;
  psVar6 = &missions_per_rank;
  sVar5 = rank;
  while (sVar5 = sVar5 + -1, sVar5 != -1) {
    sVar4 = *psVar6 + sVar4;
    psVar6 = psVar6 + 1;
  }
  DAT_0002457c = 0;
  (**(code **)(DAT_00026e6e + -0x1e))
            (*(undefined4 *)
              ((int)&map_name_table + (int)(short)((mission_in_rank + sVar4 + -1) * 4)));
  iVar2 = DAT_00026e6e;
  (**(code **)(DAT_00026e6e + -0x2a))();
  iVar1 = DAT_00026e44;
  (**(code **)(iVar2 + -0x2a))();
  carrier_home_x = (short)DAT_00026e44 * 4 + -8;
  DAT_00024578 = alloc_mem();
  iVar2 = DAT_00026e6e;
  if (DAT_00024578 != 0) {
    (**(code **)(DAT_00026e6e + -0x2a))();
    (**(code **)(iVar2 + -0x24))();
    DAT_00025316 = (short)iVar1;
    DAT_00024580 = DAT_00025316 << 2;
    iVar1 = DAT_00024578 + iVar1;
    DAT_0002457c = CONCAT22((short)((uint)iVar1 >> 0x10),(short)iVar1 + -2);
    parse_map_objects();
    return in_D0;
  }
  uVar3 = FUN_000124d8();
  return uVar3;
}


// ==== FUN_00012bbe @ 00012bbe ====

undefined8 FUN_00012bbe(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  if (DAT_000253b4._0_1_ != '\0') {
    DAT_000253b4._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  if (DAT_000253d2._0_1_ != '\0') {
    DAT_000253d2._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  if (DAT_000253f0._0_1_ != '\0') {
    DAT_000253f0._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  if (DAT_0002540e._0_1_ != '\0') {
    DAT_0002540e._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  has_own_carrier = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== parse_airfield_zones @ 00012c84 ====

undefined8 parse_airfield_zones(void)

{
  ushort uVar1;
  bool bVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar3;
  short sVar4;
  ushort *puVar5;
  short *psVar6;
  undefined *puVar7;
  undefined *puVar8;
  
  sVar3 = mission_in_rank + rank * 4;
  puVar7 = &airfield_planes_table +
           (short)(CONCAT11((char)((ushort)sVar3 >> 8),(&mission_index_table)[sVar3]) << 2);
  sVar4 = ((ushort)((uint)(DAT_0002457c - (int)DAT_00024578) >> 1) & 0x7fff) - 1;
  psVar6 = &airfield_zones;
  airfield_zones = 0;
  DAT_0002524c = 0;
  DAT_0002525e = 0;
  DAT_00025260 = 0;
  DAT_00025272 = 0;
  DAT_00025274 = 0;
  DAT_00025286 = 0;
  DAT_00025288 = 0;
  bVar2 = false;
  sVar3 = 0;
  puVar5 = DAT_00024578;
  do {
    uVar1 = *puVar5 >> 2 & 0x1ff;
    if (uVar1 == 0x114) {
      bVar2 = (bool)(bVar2 ^ 1);
      if (bVar2) {
        *psVar6 = sVar3;
      }
      else {
        psVar6[1] = sVar3;
        psVar6[7] = -1;
        psVar6[3] = 0;
        puVar8 = puVar7 + 1;
        *(undefined *)((int)psVar6 + 7) = *puVar7;
        psVar6[2] = 0;
        puVar7 = puVar7 + 2;
        *(undefined *)((int)psVar6 + 5) = *puVar8;
        psVar6 = psVar6 + 10;
      }
    }
    else if (uVar1 == 0x115) {
      bVar2 = (bool)(bVar2 ^ 1);
      if (bVar2) {
        *psVar6 = sVar3;
      }
      else {
        psVar6[1] = sVar3;
        psVar6[7] = 1;
        psVar6[3] = 0;
        puVar8 = puVar7 + 1;
        *(undefined *)((int)psVar6 + 7) = *puVar7;
        psVar6[2] = 0;
        puVar7 = puVar7 + 2;
        *(undefined *)((int)psVar6 + 5) = *puVar8;
        psVar6 = psVar6 + 10;
      }
    }
    sVar3 = sVar3 + 8;
    sVar4 = sVar4 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar4 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== parse_map_objects @ 00012d5a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 parse_map_objects(void)

{
  ushort uVar1;
  undefined4 in_D0;
  undefined4 uVar2;
  short sVar3;
  ushort uVar4;
  short *psVar5;
  short *psVar6;
  short *psVar7;
  int extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int iVar8;
  undefined4 extraout_A1;
  undefined4 extraout_A1_00;
  undefined4 extraout_A1_01;
  undefined4 extraout_A1_02;
  undefined4 *unaff_A2;
  
  island_bunker_range = 0;
  DAT_00025394 = 0;
  DAT_00025398 = 0;
  DAT_0002539c = 0;
  FUN_000129c8();
  parse_airfield_zones();
  DAT_000253d2 = 0;
  DAT_000253e2 = 0;
  DAT_000253e8 = 0;
  has_battleship = '\0';
  DAT_0002550f = 0;
  DAT_0002540e = 0;
  has_jcarrier = '\0';
  DAT_0002541e = 0;
  DAT_00025424 = 0;
  carrier_alive = 0xffff;
  DAT_0002543c = 0;
  DAT_00025442 = 0;
  DAT_000253b4 = 0;
  has_destroyer = '\0';
  DAT_000253c4 = 0;
  DAT_000253ca = 0;
  DAT_000253f0 = 0;
  has_transport = '\0';
  DAT_00025400 = 0;
  DAT_00025406 = 0;
  hut_count = '\0';
  pillbox_count = '\0';
  bunker_count = '\0';
  DAT_00025550 = '\0';
  uVar4 = 0;
  iVar8 = DAT_00024578;
  uVar2 = extraout_A1;
  do {
    if ((*(ushort *)(iVar8 + (short)uVar4) & 0x8000) != 0) {
      uVar1 = (ushort)((*(ushort *)(iVar8 + (short)uVar4) & 0xffff7fff) >> 2) & 0x1ff;
      if (uVar1 == 4) {
        DAT_00025550 = -1;
        hut_count = hut_count + '\x01';
      }
      else if (uVar1 == 3) {
        DAT_00025550 = -1;
        bunker_count = bunker_count + '\x01';
      }
      else if (uVar1 == 0xf) {
        DAT_00025550 = -1;
        pillbox_count = pillbox_count + '\x01';
      }
      else if (uVar1 == 0x21) {
        if (has_own_carrier == '\0') {
          has_own_carrier = -1;
          carrier_alive = 0xffff;
          _session_over = 0;
          carrier_deck_base_height = 0x21;
          carrier_hp = 4;
          DAT_0002543a = 0;
          DAT_0002542e = 0;
          DAT_00025432 = 0;
          DAT_0002543e = 0x14;
          ship_own_carrier = uVar4 - 0xa0;
          DAT_0002542a = uVar4 + 0x20;
        }
      }
      else if (uVar1 == 0x10d) {
        if (has_battleship == '\0') {
          has_battleship = -1;
          ships_present = ships_present + '\x01';
          ships_remaining = ships_remaining + '\x01';
          DAT_000253d2 = 0xffff;
          DAT_000253d8 = 0xe;
          DAT_000253dc = 0x1b;
          DAT_000253e0 = 0x1194;
          DAT_000253da = 2;
          ship_battleship = uVar4 - 0x20;
          DAT_000253d0 = uVar4 + 0xa0;
          unaff_A2 = (undefined4 *)&DAT_00025066;
          init_ship_plane_block(0x10d);
          uVar2 = extraout_A1_00;
        }
      }
      else if (uVar1 == 0xf2) {
        if (has_jcarrier == '\0') {
          has_jcarrier = -1;
          ships_present = ships_present + '\x01';
          ships_remaining = ships_remaining + '\x01';
          DAT_0002540e = 0xffff;
          DAT_00025414 = 0xf;
          DAT_00025418 = 0x15;
          DAT_0002541c = 6000;
          DAT_00025416 = 3;
          DAT_00025420 = 0x14;
          ship_jcarrier = uVar4 - 0x20;
          DAT_0002540c = uVar4 + 0x7c;
          unaff_A2 = (undefined4 *)&DAT_000250e6;
          init_ship_plane_block(0xf2);
          uVar2 = extraout_A1_01;
        }
      }
      else if (uVar1 == 0xe4) {
        if (has_destroyer == '\0') {
          has_destroyer = -1;
          ships_present = ships_present + '\x01';
          ships_remaining = ships_remaining + '\x01';
          DAT_000253b4 = 0xffff;
          DAT_000253ba = 8;
          DAT_000253be = 0x1b;
          DAT_000253c2 = 0x9c4;
          DAT_000253bc = 1;
          DAT_000253c6 = 0x14;
          ship_destroyer = uVar4 - 0x20;
          DAT_000253b2 = uVar4 + 0x80;
          unaff_A2 = &ship_plane_blocks;
          init_ship_plane_block(0xe4);
          uVar2 = extraout_A1_02;
        }
      }
      else if (uVar1 == 0xcc) {
        if (has_transport == '\0') {
          has_transport = -1;
          ships_present = ships_present + '\x01';
          ships_remaining = ships_remaining + '\x01';
          DAT_000253f0 = 0xffff;
          DAT_000253fa = 0x1c;
          DAT_000253f6 = 4;
          DAT_000253fe = 1000;
          DAT_000253f8 = 1;
          DAT_00025402 = 0x14;
          ship_transport = uVar4 - 0x10;
          DAT_000253ee = uVar4 + 0x10;
          init_ship_plane_block(0xcc,iVar8,uVar2,unaff_A2);
        }
      }
      else if ((uVar1 == 2) && (island_count = island_count + '\x01', DAT_00025550 != '\0')) {
        DAT_00025550 = '\0';
        enemy_island_count = enemy_island_count + '\x01';
        enemy_islands_remaining = enemy_islands_remaining + '\x01';
      }
    }
    uVar4 = uVar4 + 2;
  } while (uVar4 < DAT_00025316);
  if ((hut_count != '\0') && (huts_ptr = alloc_mem(), huts_ptr == 0)) {
    uVar2 = FUN_000124d8();
    return uVar2;
  }
  if ((((bunker_count == '\0') || (bunkers_ptr = alloc_mem(), bunkers_ptr != 0)) &&
      ((soldier_slot_count = (ushort)(byte)(bunker_count + hut_count) * 5, soldier_slot_count == 0
       || (soldiers_ptr = alloc_mem(), soldiers_ptr != 0)))) &&
     ((pillbox_count == '\0' || (pillboxes_ptr = alloc_mem(), pillboxes_ptr != 0)))) {
    sVar3 = 0;
    psVar5 = &beach_left_offsets;
    island_enemy_counts = 0;
    DAT_000253a4 = 0;
    DAT_000253a8 = 0;
    DAT_000253ac = 0;
    psVar6 = &beach_right_offsets;
    iVar8 = DAT_00024578;
    uVar4 = DAT_00025316;
    do {
      psVar7 = psVar6;
      if ((*(ushort *)(iVar8 + sVar3) & 0x8000) != 0) {
        uVar1 = (*(ushort *)(iVar8 + sVar3) & 0x7fff) >> 2 & 0x1ff;
        if (uVar1 == 4) {
          init_hut_record();
          iVar8 = extraout_A0;
        }
        else if (uVar1 == 3) {
          init_bunker_record();
          iVar8 = extraout_A0_00;
        }
        else if (uVar1 == 0xf) {
          init_pillbox_record();
          iVar8 = extraout_A0_01;
        }
        else if (uVar1 == 1) {
          *psVar5 = sVar3;
          psVar5 = psVar5 + 1;
        }
        else if (uVar1 == 2) {
          psVar7 = psVar6 + 1;
          *psVar6 = sVar3;
        }
      }
      sVar3 = sVar3 + 2;
    } while ((-1 < (short)(uVar4 - 1)) && (uVar4 = uVar4 - 2, psVar6 = psVar7, uVar4 != 0xffff));
    return in_D0;
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (*_thunk_FUN_0001020e)();
  return uVar2;
}


// ==== init_bunker_record @ 000131c8 ====

void init_bunker_record(void)

{
  short sVar1;
  undefined4 unaff_D2;
  short sVar2;
  short unaff_D7w;
  undefined4 *in_A1;
  short *unaff_A5;
  
  sVar1 = unaff_D7w * 4;
  sVar2 = (short)unaff_D2;
  if (*(short *)((int)&island_bunker_range + (int)sVar1) == 0) {
    *(short *)((int)&island_bunker_range + (int)sVar1) = sVar2;
  }
  *(short *)((int)&island_bunker_range + sVar1 + 2) = sVar2;
  *(short *)(in_A1 + 1) = sVar2 << 2;
  *(short *)(in_A1 + 1) = *(short *)(in_A1 + 1) + -0x2c;
  *(short *)((int)in_A1 + 6) = sVar2 << 2;
  *(short *)((int)in_A1 + 6) = *(short *)((int)in_A1 + 6) + 0x10;
  *in_A1 = unaff_D2;
  *(char *)((int)in_A1 + 9) = (char)unaff_D7w;
  *(undefined1 *)(in_A1 + 2) = 5;
  *unaff_A5 = *unaff_A5 + 5;
  return;
}


// ==== init_hut_record @ 00013216 ====

void init_hut_record(void)

{
  short sVar1;
  undefined4 unaff_D2;
  undefined1 unaff_D7b;
  undefined4 *unaff_A2;
  short *unaff_A5;
  
  sVar1 = (short)unaff_D2 << 2;
  *(short *)(unaff_A2 + 1) = sVar1;
  *(short *)((int)unaff_A2 + 6) = sVar1;
  *unaff_A2 = unaff_D2;
  *(undefined1 *)((int)unaff_A2 + 9) = unaff_D7b;
  *(undefined1 *)(unaff_A2 + 2) = 5;
  *unaff_A5 = *unaff_A5 + 5;
  return;
}


// ==== init_pillbox_record @ 00013236 ====

void init_pillbox_record(void)

{
  undefined2 unaff_D2w;
  undefined2 *unaff_D6;
  undefined2 unaff_D7w;
  int unaff_A5;
  
  *unaff_D6 = unaff_D2w;
  unaff_D6[3] = unaff_D7w;
  *(short *)(unaff_A5 + 2) = *(short *)(unaff_A5 + 2) + 1;
  unaff_D6[2] = 0;
  return;
}


// ==== load_ship_shapes @ 00013252 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void load_ship_shapes(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int extraout_A0_02;
  int extraout_A0_03;
  
  DAT_00025444 = 0;
  if (has_battleship != '\0') {
    DAT_00026e88 = (*_load_shape_bank)();
    if (DAT_00026e88 == 0) {
      DAT_0002550f = 0xff;
      has_battleship = '\0';
    }
    DAT_000253ea = 0xf8;
    DAT_00026e84 = extraout_A0;
    alloc_ship_guns();
  }
  if (has_destroyer != '\0') {
    uVar2 = (*_load_shape_bank)();
    DAT_000253cc = 0xd0;
    DAT_00026e94 = extraout_A0_00;
    if (extraout_A0_00 == 0) {
      FUN_000124d8();
      return;
    }
    DAT_00026e98 = uVar2;
    alloc_ship_guns();
  }
  if (has_transport != '\0') {
    uVar2 = (*_load_shape_bank)();
    DAT_00025408 = 0xb8;
    DAT_00026e9c = extraout_A0_01;
    if (extraout_A0_01 == 0) {
      FUN_000124d8();
      return;
    }
    DAT_00026ea0 = uVar2;
    alloc_ship_guns();
    iVar1 = *(int *)(extraout_A0_02 + 6);
    *(undefined2 *)(iVar1 + 0x14) = 5;
    *(undefined2 *)(iVar1 + 0x22) = 5;
  }
  if (has_jcarrier != '\0') {
    uVar2 = (*_load_shape_bank)();
    DAT_00026e8c = extraout_A0_03;
    if (extraout_A0_03 == 0) {
      FUN_000124d8();
      return;
    }
    DAT_00025426 = 0;
    DAT_00026e90 = uVar2;
    alloc_ship_guns();
  }
  return;
}


// ==== load_sounds @ 00013368 ====

void load_sounds(void)

{
  if (snd_engine == 0) {
    DAT_000254ca = FUN_00015b1a();
    snd_engine = FUN_00015d50();
  }
  if (snd_splash == 0) {
    DAT_000254ce = FUN_00015b1a();
    snd_splash = FUN_00015d50();
  }
  if (snd_screech == 0) {
    DAT_000254da = FUN_00015b1a();
    snd_screech = FUN_00015d50();
  }
  if (snd_scream == 0) {
    DAT_000254d2 = FUN_00015b1a();
    snd_scream = FUN_00015d50();
  }
  if (snd_metal_clang == 0) {
    DAT_000254d6 = FUN_00015b1a();
    snd_metal_clang = FUN_00015d50();
  }
  if (snd_boom == 0) {
    DAT_000254c6 = FUN_00015b1a();
    snd_boom = FUN_00015d50();
  }
  if (snd_grind == 0) {
    DAT_000254de = FUN_00015b1a();
    snd_grind = FUN_00015d50();
  }
  if (snd_machinegun == 0) {
    DAT_000254c2 = FUN_00015b1a();
    snd_machinegun = FUN_00015d50();
  }
  init_sound_slots();
  return;
}


// ==== load_engine_sound @ 0001344e ====

void load_engine_sound(void)

{
  if (snd_engine == 0) {
    DAT_000254ca = FUN_00015b1a();
    snd_engine = FUN_00015d50();
  }
  return;
}


// ==== free_sounds @ 0001346c ====

void free_sounds(void)

{
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  return;
}


// ==== FUN_000134a4 @ 000134a4 ====

void FUN_000134a4(void)

{
  FUN_000124e0();
  return;
}


// ==== FUN_000134ae @ 000134ae ====

void FUN_000134ae(void)

{
  FUN_00012502();
  return;
}


// ==== FUN_000134bc @ 000134bc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000134bc(void)

{
  FUN_000125c6();
  (*_thunk_FUN_000205cc)();
  load_ticker_font();
  FUN_0001283e();
  FUN_000129dc();
  return;
}


// ==== FUN_000134d8 @ 000134d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000134d8(void)

{
  FUN_00012a92();
  FUN_0001295a();
  FUN_000128d6();
  FUN_000127f6();
  (*_thunk_FUN_0002067c)();
  FUN_0001276c();
  FUN_0001660e();
  (*_thunk_FUN_0002090a)(0xffffffff);
  (**(code **)(DAT_00026e76 + -0xd2))();
  FUN_0001259e();
  return;
}


// ==== alloc_ship_guns @ 0001350e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 alloc_ship_guns(void)

{
  short sVar1;
  undefined4 in_D0;
  int iVar2;
  short sVar3;
  undefined4 in_D1;
  short *extraout_A0;
  undefined2 *extraout_A1;
  undefined2 *puVar4;
  undefined8 uVar5;
  
  if (DAT_00026c90 != 0) {
    return CONCAT44(in_D0,in_D1);
  }
  iVar2 = alloc_mem();
  *(int *)(extraout_A0 + 3) = iVar2;
  if (iVar2 == 0) {
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar5 = (*_thunk_FUN_0001020e)();
    return uVar5;
  }
  sVar1 = *extraout_A0;
  sVar3 = extraout_A0[5];
  puVar4 = extraout_A1;
  while (sVar3 = sVar3 + -1, sVar3 != -1) {
    *(undefined2 *)(iVar2 + 4) = *puVar4;
    *(short *)(iVar2 + 4) = sVar1 * 4 + *(short *)(iVar2 + 4);
    iVar2 = iVar2 + 0xe;
    puVar4 = puVar4 + 1;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00013554 @ 00013554 ====

void FUN_00013554(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  sVar1 = 0x4f;
  puVar2 = &airfield_zones;
  do {
    *(undefined1 *)puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = (undefined2 *)((int)puVar2 + 1);
  } while (sVar1 != -1);
  return;
}


// ==== new_game_init @ 00013562 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void new_game_init(void)

{
  carrier_hp = 4;
  score = 0;
  mission_complete = 0;
  _session_over = 0;
  DAT_000252ae = 0xff;
  lives = 3;
  gravity = 0x6000;
  DAT_000252a4 = 0x400;
  DAT_000252a8 = 0x55;
  DAT_000252aa = 0xa0;
  (*_hud_set_lives_drum)();
  (*_clear_enemy_planes)();
  reset_enemy_state();
  return;
}


// ==== reset_enemy_state @ 000135a8 ====

void reset_enemy_state(void)

{
  victory_balloons = 0;
  enemy_planes = 0;
  DAT_000251ae = 0;
  DAT_000251e2 = 0;
  DAT_00025216 = 0;
  zeros_airborne = 0;
  wreck_count = 0;
  paused = 0;
  respawn_on_carrier();
  return;
}


// ==== lose_life_and_respawn @ 000135ce ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 lose_life_and_respawn(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  int iVar2;
  
  respawn_blank_frames = 0x14;
  lives = lives + -1;
  player_x = carrier_home_x;
  turn_frame = 0;
  player_dir = 0xffff;
  sVar1 = 0x27;
  iVar2 = smoke_particles_ptr;
  do {
    *(undefined2 *)(iVar2 + 0x10) = 0;
    iVar2 = iVar2 + 0x14;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if ((lives < '\x01') || (carrier_hp < 1)) {
    game_over_display = 0xff;
    session_over = 0xff;
    lives = '\0';
  }
  else {
    deck_crew_signal = 3;
    DAT_000252b0 = 0;
    rearm_new_plane();
    if (respawn_blank_frames != 0) {
      (*_clip_playfield)();
      (*_set_rastport)();
      (*_own_blitter)();
      (*_fill_rect)();
      (*_wait_disown_blitter)();
      FUN_0001030c();
      do {
        (*_thunk_FUN_00022eee)();
        respawn_blank_frames = respawn_blank_frames + -1;
      } while (respawn_blank_frames != 0);
      do {
        (*_thunk_FUN_00022eee)();
      } while (respawn_blank_frames != 0);
    }
  }
  respawn_blank_frames = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== respawn_on_carrier @ 000135d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 respawn_on_carrier(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  int iVar2;
  
  player_x = carrier_home_x;
  turn_frame = 0;
  player_dir = 0xffff;
  sVar1 = 0x27;
  iVar2 = smoke_particles_ptr;
  do {
    *(undefined2 *)(iVar2 + 0x10) = 0;
    iVar2 = iVar2 + 0x14;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if ((lives < '\x01') || (carrier_hp < 1)) {
    game_over_display = 0xff;
    session_over = 0xff;
    lives = '\0';
  }
  else {
    deck_crew_signal = 3;
    DAT_000252b0 = 0;
    rearm_new_plane();
    if (respawn_blank_frames != 0) {
      (*_clip_playfield)();
      (*_set_rastport)();
      (*_own_blitter)();
      (*_fill_rect)();
      (*_wait_disown_blitter)();
      FUN_0001030c();
      do {
        (*_thunk_FUN_00022eee)();
        respawn_blank_frames = respawn_blank_frames + -1;
      } while (respawn_blank_frames != 0);
      do {
        (*_thunk_FUN_00022eee)();
      } while (respawn_blank_frames != 0);
    }
  }
  respawn_blank_frames = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== rearm_new_plane @ 00013684 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 rearm_new_plane(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_00026c8e = 0xf;
  (*_clear_projectiles)();
  weapon_type = 1;
  sky_flash_count = 0;
  player_airspeed = 0;
  deck_crew_signal = 3;
  DAT_000255dc = 0;
  (*_engine_sound_off)();
  gun_ammo = 0x600;
  carrier_phase = 1;
  elevator_offset = 0x20;
  waterline_y = 0x97;
  carrier_menu_active = 0xff;
  DAT_000252b6 = 0x20;
  DAT_000252b7 = 0xff;
  wave_frame_delay = 1;
  DAT_000252b9 = 5;
  DAT_000252f2 = frame_counter_mod100;
  gun_firing = 0;
  frame_counter_mod11 = 0;
  DAT_000252bc = 0;
  if (ordnance_count != -1) {
    ordnance_count = (&ordnance_per_weapon)[weapon_type];
  }
  (*_hud_set_ammo_drum)();
  DAT_000252f8 = 2;
  bob_timer = 0xffff;
  zoom_request = 8;
  DAT_00025302 = 1;
  DAT_00025304 = 3;
  DAT_00025306 = 3;
  DAT_00025308 = 1;
  DAT_0002530a = 0x16;
  weapon_menu_debounce = 1;
  DAT_000252bf = 1;
  (*_player_reset)();
  return CONCAT44(in_D0,in_D1);
}


// ==== clear_projectiles @ 00013756 ====

void clear_projectiles(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  puVar2 = &projectiles;
  sVar1 = 0xe;
  do {
    *(undefined1 *)(puVar2 + 0x10) = 0;
    puVar2 = puVar2 + 0x15;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00025504._0_1_ = 0;
  return;
}


// ==== render_world @ 00013772 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void render_world(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  ushort *puVar4;
  
  DAT_000273a8 = 0;
  aa_firing_flag = 0;
  aa_nearest_dist = 10000;
  (*_own_blitter)();
  (*_fill_rect)();
  frame_counter_mod100 = frame_counter_mod100 + 1;
  if (frame_counter_mod100 == 100) {
    frame_counter_mod100 = 0;
  }
  uVar1 = render_player_x;
  if (view_scale == 1) {
    uVar1 = render_player_x & 0xfff8;
  }
  sVar2 = 0x120;
  if (view_scale != 8) {
    sVar2 = 0x900;
  }
  puVar4 = (ushort *)((int)(short)((short)(uVar1 - sVar2) >> 2 & 0xfffe) + (int)DAT_00024578);
  sVar2 = -0x78 - (uVar1 & 7);
  view3d_horizon_y = (render_player_y >> 4) + 0x18;
  iVar3 = cell_frames;
  if (view_scale == 1) {
    iVar3 = cell_frames_eighth;
  }
  do {
    if (DAT_00024578 <= puVar4) goto LAB_00013842;
    puVar4 = puVar4 + 1;
    sVar2 = view_scale + sVar2;
  } while (sVar2 < 0x1d0);
  goto LAB_000138ba;
  while( true ) {
    uVar1 = *puVar4 >> 2;
    if (((uVar1 & 0x2000) != 0) && (*(int *)(iVar3 + (short)((uVar1 & 0x1ff) << 2)) != 0)) {
      if ((*puVar4 & 3) == 1) {
        FUN_00014eac();
      }
      (*_draw_shape_automask)();
    }
    draw_special_map_cell();
    sVar2 = view_scale + sVar2;
    puVar4 = puVar4 + 1;
    if (0x1cf < sVar2) break;
LAB_00013842:
    if (DAT_0002457c < puVar4 + 1) break;
  }
LAB_000138ba:
  FUN_00013abc();
  draw_carrier_elevator();
  (*_draw_player_plane)();
  (*_draw_enemy_planes_and_wrecks)();
  update_bunkers();
  update_pillboxes();
  update_ship_guns();
  draw_airfield_planes();
  draw_ship_deck_planes();
  draw_sea_waves();
  FUN_000140e8();
  (*_wait_disown_blitter)();
  if (aa_firing_flag == 0) {
    _aa_gun_sound = 0;
  }
  else {
    uVar1 = aa_nearest_dist >> 3;
    if (0x40 < uVar1) {
      uVar1 = 0x40;
    }
    aa_gun_volume = 0x40 - uVar1;
    _aa_gun_sound = CONCAT11(0xff,aa_gun_sound_1);
  }
  DAT_000273a8 = 0;
  return;
}


// ==== draw_ship_deck_planes @ 0001391e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_ship_deck_planes(void)

{
  short sVar1;
  short *psVar2;
  undefined **ppuVar3;
  short sVar4;
  short sVar5;
  short *psVar6;
  short *unaff_A3;
  undefined **ppuVar7;
  
  sVar1 = clip_bottom;
  sVar5 = 4;
  psVar2 = (short *)&ship_plane_blocks_render_copy;
  ppuVar3 = &ship_ptr_list;
  do {
    ppuVar7 = ppuVar3;
    psVar6 = psVar2;
    sVar4 = 0;
    if (*(short *)(*ppuVar7 + 4) != 0) {
      if (zoom_shift == 0) {
        if ((sVar5 < 1) &&
           (sVar4 = wave_bob_offset + *(short *)(*ppuVar7 + 0x1a) + 0x8e, sVar4 < clip_bottom)) {
          clip_bottom = sVar4;
        }
      }
      else {
        clip_bottom = 0x96;
      }
      unaff_A3 = psVar6 + 4;
      sVar4 = *psVar6;
    }
    while (sVar4 = sVar4 + -1, sVar4 != -1) {
      if (*unaff_A3 != 0) {
        (*_draw_world_object)();
      }
      unaff_A3 = unaff_A3 + 4;
    }
    sVar5 = sVar5 + -1;
    psVar2 = psVar6 + 0x20;
    ppuVar3 = ppuVar7 + 1;
  } while (sVar5 != -1);
  if ((((0 < *psVar6) && (zoom_shift == 0)) &&
      (sVar5 = (*(short *)*ppuVar7 * 4 + 0x199) - camera_left_x, -0x81 < sVar5)) && (sVar5 < 0x1c1))
  {
    clip_bottom = sVar1;
    (*_draw_shape_automask)();
  }
  clip_bottom = sVar1;
  return;
}


// ==== draw_airfield_planes @ 00013a18 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 draw_airfield_planes(void)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  undefined2 *puVar4;
  
  sVar3 = 3;
  puVar4 = &airfield_zones;
  do {
    sVar2 = puVar4[8];
    uVar1 = 0;
    if (puVar4[1] != 0) {
      while (sVar2 = sVar2 + -1, sVar2 != -1) {
        (*_draw_shape_automask)();
      }
      uVar1 = 0;
      if (puVar4[9] != 0) {
        uVar1 = (*_draw_shape_automask)();
      }
    }
    puVar4 = puVar4 + 10;
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  return uVar1;
}


// ==== FUN_00013abc @ 00013abc ====

/* WARNING: Removing unreachable block (ram,0x00013ae2) */
/* WARNING: Removing unreachable block (ram,0x00013afe) */
/* WARNING: Removing unreachable block (ram,0x00013b02) */
/* WARNING: Removing unreachable block (ram,0x00013b12) */
/* WARNING: Removing unreachable block (ram,0x00013b0a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013abc(void)

{
  return;
}


// ==== draw_special_map_cell @ 00013b1c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_special_map_cell(void)

{
  short sVar1;
  undefined2 uVar2;
  undefined4 in_D0;
  short sVar4;
  uint uVar3;
  undefined4 in_D1;
  ushort unaff_D3w;
  ushort uVar5;
  short unaff_D4w;
  ushort *puVar6;
  int *piVar7;
  
  uVar5 = unaff_D3w & 0xdfff;
  uVar2 = (undefined2)((uint)in_D0 >> 0x10);
  if (((unaff_D3w & 0x2000) != 0) && (uVar5 == 5)) {
    if (view_scale == 1) {
      uVar5 = (unaff_D4w * 8 + (render_player_x & 0xfff8)) - 0x538;
    }
    else {
      uVar5 = unaff_D4w + (render_player_x - 0xa0);
      uVar2 = 0;
    }
    uVar3 = CONCAT22(uVar2,uVar5 >> 2) & 0xfffffffe;
    for (piVar7 = huts_ptr; CONCAT22((short)(uVar3 >> 0x10),(short)uVar3 + -2) != *piVar7;
        piVar7 = piVar7 + 4) {
    }
    if (((*(short *)(piVar7 + 3) != 0) &&
        (sVar4 = *(short *)((int)piVar7 + 0xe), sVar1 = sVar4 + -1,
        *(short *)((int)piVar7 + 0xe) = sVar1, sVar1 == 0 || sVar4 < 1)) &&
       (sVar4 = *(short *)(piVar7 + 3) + -1, *(short *)(piVar7 + 3) = sVar4, sVar4 != 0)) {
      *(short *)((int)piVar7 + 0xe) = 0x32 - *(short *)(piVar7 + 3);
      (*_spawn_smoke_particle)();
    }
    return CONCAT44(in_D0,in_D1);
  }
  if (view_scale == 1) {
    return CONCAT44(in_D0,in_D1);
  }
  if (uVar5 == 0x22) {
    if (((frame_counter_mod100 & 1) != 0) &&
       (DAT_000252dd = DAT_000252dd - 1, (short)((ushort)DAT_000252dd << 8) < 0)) {
      DAT_000252dd = 3;
    }
    (*_draw_shape_automask)();
    return CONCAT44(in_D0,in_D1);
  }
  if (uVar5 == 0x9f) {
    if (DAT_000273a8 == '\0') {
      DAT_000273a8 = -1;
      if (deck_crew_signal != DAT_000255dc) {
        DAT_000255dc = deck_crew_signal;
        DAT_000255a4 = *(short *)(&DAT_000255ae + (short)((ushort)deck_crew_signal << 2));
        DAT_000255a8 = *(short *)(&DAT_000255c6 + (short)((ushort)deck_crew_signal << 2));
      }
      sVar4 = 1;
      if (DAT_000255a6 == DAT_000255a4) {
        if ((DAT_000255dc != 2) || (DAT_000255a6 == DAT_000255aa)) {
          DAT_000255a4 = *(short *)(&DAT_000255ac + (short)((ushort)DAT_000255dc << 2));
          if (DAT_000255a4 == DAT_000255a6) {
            DAT_000255a4 = *(short *)(&DAT_000255ae + (short)((ushort)DAT_000255dc << 2));
          }
        }
      }
      else {
        if (DAT_000255a4 <= DAT_000255a6) {
          sVar4 = -1;
        }
        DAT_000255a6 = sVar4 + DAT_000255a6;
      }
      sVar4 = 1;
      if (DAT_000255aa == DAT_000255a8) {
        DAT_000255a8 = *(short *)(&DAT_000255c4 + (short)((ushort)DAT_000255dc << 2));
        if (DAT_000255a8 == DAT_000255aa) {
          DAT_000255a8 = *(short *)(&DAT_000255c6 + (short)((ushort)DAT_000255dc << 2));
        }
      }
      else {
        if (DAT_000255a8 <= DAT_000255aa) {
          sVar4 = -1;
        }
        DAT_000255aa = sVar4 + DAT_000255aa;
      }
    }
    (*_draw_shape_automask)();
    (*_draw_shape_automask)();
    return CONCAT44(in_D0,in_D1);
  }
  if (uVar5 == 0x113) {
    sVar4 = 0;
    puVar6 = &beach_right_offsets;
    while (*puVar6 <= render_player_x >> 2) {
      sVar4 = sVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    if (((*(short *)((int)&island_enemy_counts + (int)(short)(sVar4 * 4)) != 0) ||
        (*(short *)((int)&island_enemy_counts + (short)(sVar4 * 4) + 2) != 0)) &&
       (island_flag_anim = island_flag_anim - 1, (short)((ushort)island_flag_anim << 8) < 0)) {
      island_flag_anim = 2;
    }
    (*_draw_shape_automask)();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== update_bunkers @ 00013d78 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_bunkers(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  int *piVar4;
  bool bVar5;
  
  uVar3 = (ushort)bunker_count;
  piVar4 = bunkers_ptr;
  while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
    if (*(char *)(piVar4 + 2) == '\0') {
      sVar1 = *(short *)((int)piVar4 + 0xe);
      sVar2 = sVar1 + -1;
      *(short *)((int)piVar4 + 0xe) = sVar2;
      if (sVar2 == 0 || sVar1 < 1) {
        *(undefined2 *)((int)piVar4 + 0xe) = 200;
        send_soldier_to_empty_bunker();
      }
    }
    else if ((*(short *)(piVar4 + 3) == 0) ||
            (sVar1 = *(short *)(piVar4 + 3) + -1, *(short *)(piVar4 + 3) = sVar1, sVar1 == 0)) {
      bVar5 = *piVar4 < 0;
      aa_gun_aim_frame();
      if (!bVar5) {
        (*_draw_world_object)();
        aa_gun_hit_roll();
      }
    }
    piVar4 = piVar4 + 4;
  }
  return;
}


// ==== update_pillboxes @ 00013de8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_pillboxes(void)

{
  short sVar1;
  short sVar2;
  int in_D0;
  int iVar3;
  ushort uVar4;
  short *psVar5;
  bool bVar6;
  
  uVar4 = (ushort)pillbox_count;
  psVar5 = pillboxes_ptr;
  while (uVar4 = uVar4 - 1, uVar4 != 0xffff) {
    if (*(char *)(psVar5 + 4) == '\0') {
      iVar3 = CONCAT22((short)((uint)in_D0 >> 0x10),*psVar5 * 4);
      bVar6 = in_D0 < 0;
      aa_gun_aim_frame();
      if (!bVar6) {
        (*_draw_world_object)();
        iVar3 = aa_gun_hit_roll();
      }
    }
    else {
      iVar3 = in_D0;
      if (((psVar5[5] != 0) &&
          (sVar1 = psVar5[6], sVar2 = sVar1 + -1, psVar5[6] = sVar2, sVar2 == 0 || sVar1 < 1)) &&
         (sVar1 = psVar5[5] + -1, psVar5[5] = sVar1, sVar1 != 0)) {
        psVar5[6] = 0x32 - psVar5[5];
        iVar3 = (*_spawn_smoke_particle)();
      }
    }
    psVar5 = psVar5 + 7;
    in_D0 = iVar3;
  }
  return;
}


// ==== draw_sea_waves @ 00013e6c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_sea_waves(void)

{
  if (view_scale != 8) {
    (*_fill_rect)();
    return;
  }
  (*_draw_shape_automask)();
  (*_draw_shape_automask)();
  (*_draw_shape_automask)();
  (*_draw_shape_automask)();
  (*_draw_shape_automask)();
  return;
}


// ==== update_draw_soldiers @ 00013eee ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_draw_soldiers(void)

{
  short *psVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  short sVar5;
  char cVar6;
  short extraout_D1w;
  short sVar7;
  uint uVar8;
  int extraout_A0;
  short *psVar9;
  bool bVar10;
  
  (*_own_blitter)();
  psVar9 = soldiers_ptr;
  sVar7 = soldier_slot_count;
  do {
    sVar7 = sVar7 + -1;
    if (sVar7 == -1) {
LAB_00014092:
      (*_wait_disown_blitter)();
      return;
    }
    if (psVar9[3] != 0) {
      if (psVar9[3] != 3) {
        if (psVar9[3] == 2) {
          bVar2 = *(byte *)(psVar9 + 2) - 1;
          *(byte *)(psVar9 + 2) = bVar2;
          if ((short)((ushort)bVar2 << 8) < 0) {
            *(undefined1 *)(psVar9 + 2) = 2;
            *(char *)((int)psVar9 + 3) = *(char *)((int)psVar9 + 3) + '\x01';
            if (7 < *(byte *)((int)psVar9 + 3)) {
              psVar9[3] = 3;
              score = score + 0x19;
              soldiers_killed = soldiers_killed + 1;
              sVar3 = (ushort)*(byte *)((int)psVar9 + 5) * 4;
              psVar1 = (short *)((int)&island_enemy_counts + (int)sVar3);
              sVar5 = *psVar1 + -1;
              *psVar1 = sVar5;
              if ((sVar5 == 0) && (*(short *)((int)&island_enemy_counts + sVar3 + 2) == 0)) {
                uVar4 = get_island_bonus();
                uVar8 = (uint)uVar4;
                score = uVar8 + score;
                bVar10 = SBORROW1(enemy_islands_remaining,'\x01');
                enemy_islands_remaining = enemy_islands_remaining - 1;
                if ((enemy_islands_remaining == 0 ||
                     bVar10 != (short)((ushort)enemy_islands_remaining << 8) < 0) &&
                   (ships_remaining == '\0')) {
                  (*_format_string)();
                  (*_advance_mission)(uVar8);
                  goto LAB_00014092;
                }
                (*_ticker_printf)(uVar8);
              }
            }
          }
        }
        else {
          *(char *)((int)psVar9 + 3) = *(char *)((int)psVar9 + 3) + '\x01';
          if (4 < *(byte *)((int)psVar9 + 3)) {
            *(undefined1 *)((int)psVar9 + 3) = 0;
          }
          sVar5 = 3;
          if (*(char *)(psVar9 + 1) < '\0') {
            sVar5 = -3;
          }
          cVar6 = (*_map_cell_at_x)();
          if (cVar6 == '\0') {
            sVar5 = -sVar5;
            *(char *)(psVar9 + 1) = -*(char *)(psVar9 + 1);
          }
          *psVar9 = sVar5 + *psVar9;
        }
      }
      if (((((view_scale == 8) || (psVar9[3] != 3)) && ((*_draw_world_object)(), psVar9[3] == 1)) &&
          (((*_map_cell_at_x)(), extraout_D1w == 3 && (-1 < *psVar9)))) &&
         (cVar6 = find_ground_object_record(), -1 < cVar6)) {
        if ((*(short *)(extraout_A0 + 0xc) == 0) && (*(char *)(extraout_A0 + 8) == '\0')) {
          *(undefined2 *)(extraout_A0 + 0xc) = 0x168;
        }
        *(char *)(extraout_A0 + 8) = *(char *)(extraout_A0 + 8) + '\x01';
        psVar9[3] = 0;
      }
    }
    psVar9 = psVar9 + 4;
  } while( true );
}


// ==== draw_carrier_elevator @ 0001409c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_carrier_elevator(void)

{
  if (view_scale == 8) {
    if (carrier_phase != 1) {
      (*_clip_to_deck)();
      (*_draw_world_object)();
    }
    (*_clip_playfield)();
  }
  return;
}


// ==== FUN_000140e8 @ 000140e8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000140e8(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar1;
  
  uVar1 = (ushort)island_count;
  while (uVar1 = uVar1 - 1, uVar1 != 0xffff) {
    (*_draw_world_object)();
    (*_draw_world_object)();
    (*_fill_rect)();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== draw_3d_view @ 0001417e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_3d_view(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_own_blitter)();
  (*_clip_3d_view)();
  DAT_00025332 = view3d_horizon_y;
  clear_3d_view();
  if (view_scale != 1) {
    draw_3d_view_objects();
    draw_3d_view_reticle();
  }
  (*_wait_disown_blitter)();
  return CONCAT44(in_D0,in_D1);
}


// ==== draw_3d_view_reticle @ 000141b4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_3d_view_reticle(void)

{
  if (render_player_y < 0x51) {
    DAT_0002530a = ((ushort)(0x51U - render_player_y) >> 2) + 0xd;
  }
  else {
    DAT_0002530a = 0xd;
  }
  (*_draw_shape_automask)();
  return;
}


// ==== draw_3d_view_objects @ 00014206 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_3d_view_objects(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  undefined4 in_D0;
  short sVar4;
  undefined4 in_D1;
  ushort extraout_D1w;
  ushort uVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  int extraout_A0;
  short *psVar11;
  short *psVar12;
  
  iVar3 = DAT_00024578;
  DAT_000273aa = 4;
  if ((((-1 < (short)render_player_x) && (render_player_x < DAT_00024580)) &&
      ((*(ushort *)(DAT_00024578 + (short)((render_player_x >> 3) * 2)) & 3) == 1)) &&
     ((find_ship_at_offset(), *(short *)(extraout_A0 + 0x12) == 0 ||
      (*(short *)(extraout_A0 + 0x12) == 6000)))) {
    DAT_000273aa = extraout_D1w;
  }
  psVar12 = &DAT_00024606;
  sVar10 = 10;
  do {
    sVar4 = *psVar12;
    psVar12 = psVar12 + -1;
    DAT_00025328 = 0xffff;
    DAT_0002532a = 0xffff;
    sVar7 = sVar4 - *psVar12;
    if (player_dir < 0) {
      sVar4 = -sVar4;
    }
    sVar2 = player_dir * 2;
    sVar9 = (((short)render_player_x >> 3) + sVar4) * 2;
    sVar4 = sVar7 * 2;
    if (-1 < sVar2) {
      sVar4 = sVar7 * -2;
    }
    sVar4 = sVar9 + sVar4;
    sVar6 = sVar9;
    if (sVar9 < sVar4) {
      sVar6 = sVar4;
      sVar4 = sVar9;
    }
    sVar8 = 3;
    psVar11 = &enemy_planes;
    do {
      if (((*psVar11 != 0) && (sVar4 <= psVar11[0x17])) && (psVar11[0x17] <= sVar6)) {
        (*_draw_shape_automask)();
      }
      psVar11 = psVar11 + 0x1a;
      sVar8 = sVar8 + -1;
    } while (sVar8 != -1);
    sVar4 = 0;
    do {
      if ((-1 < sVar9) && ((ushort *)(iVar3 + sVar9) <= DAT_0002457c)) {
        uVar5 = *(ushort *)(iVar3 + sVar9);
        uVar1 = uVar5 & 3;
        uVar5 = uVar5 & 0x7fc;
        DAT_000255dd = (char)uVar1;
        if (uVar1 == DAT_000273aa) {
          uVar5 = 0;
        }
        uVar5 = uVar5 >> 2;
        uVar1 = DAT_0002532a;
        if (((uVar5 != 0) &&
            (((uVar5 < 6 || (uVar1 = uVar5, 8 < uVar5)) &&
             (uVar1 = DAT_0002532a, DAT_00025328 != 0x22)))) && (DAT_00025328 != 0xf6)) {
          DAT_00025328 = uVar5;
        }
        DAT_0002532a = uVar1;
        if (DAT_000255dd == '\x02') {
          sVar4 = -1;
        }
      }
      sVar9 = sVar2 + sVar9;
      sVar7 = sVar7 + -1;
    } while (sVar7 != -1);
    if (sVar4 != 0) {
      (*_fill_rect)();
    }
    if ((-1 < (short)DAT_0002532a) && (sVar4 = FUN_000145a6(), -1 < sVar4)) {
      (*_draw_shape_automask)();
    }
    if ((-1 < (short)DAT_00025328) && (sVar4 = FUN_000145a6(), -1 < sVar4)) {
      (*_draw_shape_automask)();
    }
    DAT_00025332 = DAT_00025332 + 1;
    sVar10 = sVar10 + -1;
  } while (sVar10 != -1);
  if (DAT_0002764c == '\0') {
    draw_3d_view_carrier();
    DAT_0002764c = '\0';
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== draw_3d_view_carrier @ 00014430 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_3d_view_carrier(void)

{
  short sVar1;
  undefined4 in_D0;
  short sVar2;
  undefined4 in_D1;
  short sVar3;
  
  DAT_0002764e = clip_top;
  if (((-1 < (short)render_player_x) && (render_player_x < DAT_00024580)) &&
     (sVar1 = (render_player_x >> 3) * 2, (*(ushort *)(DAT_00024578 + sVar1) & 3) == 1)) {
    sVar3 = 0;
    DAT_00025334 = 0x49;
    sVar2 = 2;
    if (-1 < player_dir) {
      DAT_00025334 = 0x41;
      sVar2 = -2;
    }
    while ((*(ushort *)(sVar1 + DAT_00024578 + (int)sVar3) >> 2 & 0x1ff) != 0) {
      sVar3 = sVar2 + sVar3;
    }
    sVar3 = sVar3 >> 1;
    if (sVar3 < 0) {
      sVar3 = -sVar3;
    }
    clip_top = view3d_horizon_y +
               (ushort)(byte)(&DAT_00024685)[(short)(ushort)(byte)(&DAT_0002461f)[sVar3]];
    (*_draw_shape_automask)();
    (*_draw_shape_automask)();
    clip_top = DAT_0002764e;
    (*_draw_shape_automask)();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== clear_3d_view @ 00014564 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 clear_3d_view(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_set_rastport)();
  (*_fill_rect)();
  (*_fill_rect)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000145a6 @ 000145a6 ====

undefined8 FUN_000145a6(void)

{
  undefined4 in_D0;
  short sVar2;
  undefined4 uVar1;
  undefined4 in_D1;
  short sVar3;
  short extraout_D1w;
  short unaff_D7w;
  int extraout_A0;
  
  sVar2 = (short)in_D0;
  if ((5 < sVar2) && (sVar2 < 9)) {
    sVar3 = 0xe;
LAB_000146ae:
    return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),
                             ((ushort)(byte)(&DAT_00024608)[unaff_D7w] + sVar3) * 4),in_D1);
  }
  if ((sVar2 == 4) || (sVar2 == 5)) {
    sVar3 = 0x1b;
    if (sVar2 != 4) {
      sVar3 = 0x22;
    }
    goto LAB_000146ae;
  }
  if (sVar2 == 3) {
    sVar3 = 0x14;
    goto LAB_000146ae;
  }
  if ((char)in_D1 != '\x01') {
    if ((sVar2 < 0xf) || (0x1e < sVar2)) {
      return CONCAT44(0xffffffff,in_D1);
    }
    if (sVar2 == 0xf) {
      sVar3 = 0x29;
    }
    else {
      sVar3 = 0x30;
    }
    goto LAB_000146ae;
  }
  sVar3 = 10;
  if (-1 < player_dir) {
    sVar3 = 0;
  }
  if ((sVar2 == 0x22) || (sVar2 == 0xf6)) {
    sVar3 = sVar3 + 0x4d;
  }
  else {
    uVar1 = find_ship_at_offset();
    if ((short)uVar1 < 0) goto LAB_00014678;
    sVar3 = *(short *)(extraout_A0 + 0x1c);
    in_D0 = CONCAT22((short)((uint)uVar1 >> 0x10),sVar3);
    if (sVar3 == 0) {
      DAT_0002764c = 0;
      sVar3 = extraout_D1w + 0x3c;
    }
    else {
      sVar3 = sVar3 + extraout_D1w;
      DAT_0002764c = 0xff;
    }
  }
  uVar1 = CONCAT22((short)((uint)in_D0 >> 0x10),
                   ((ushort)(byte)(&DAT_00024614)[unaff_D7w] + sVar3) * 4);
LAB_00014678:
  return CONCAT44(uVar1,in_D1);
}


// ==== ground_impact_at_cell @ 000146c6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 ground_impact_at_cell(int param_1)

{
  short *psVar1;
  ushort uVar2;
  short sVar3;
  short sVar5;
  char cVar7;
  int iVar4;
  ushort uVar6;
  undefined4 in_D1;
  ushort extraout_D1w;
  short sVar8;
  uint uVar9;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  bool bVar10;
  
  param_1 = param_1 - DAT_00024578;
  uVar6 = (ushort)param_1;
  sVar5 = uVar6 * 4;
  DAT_00027672 = 0;
  DAT_00027650 = sVar5;
  cVar7 = (*_map_cell_at_x)();
  if ((cVar7 == '\0') || (uVar2 = extraout_D1w & 0x1fff, cVar7 == '\x01')) {
    iVar4 = find_ship_at_x();
    if ((-1 < iVar4) && (DAT_00027672 != 1)) {
      if ((DAT_00027672 == 2) && (sky_flash_count = 5, cRam0002766e == '\n')) {
        sky_flash_color = 0xf00;
        if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
           (sVar8 = *(short *)(extraout_A0_02 + 0xc) + -1, *(short *)(extraout_A0_02 + 0xc) = sVar8,
           sVar8 == 0)) {
          *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
        }
      }
      else {
        sky_flash_count = 5;
        sky_flash_color = 0xfff;
        iVar4 = *(int *)(extraout_A0_02 + 6);
        if (iVar4 != 0) {
          sVar8 = *(short *)(extraout_A0_02 + 10);
          while (sVar8 = sVar8 + -1, sVar8 != -1) {
            if (*(short *)(iVar4 + 8) == 0) {
              uVar6 = sVar5 - *(short *)(iVar4 + 4);
              if ((int)((uint)uVar6 << 0x10) < 0) {
                uVar6 = -uVar6;
              }
              if ((short)uVar6 < 0x10) {
                *(undefined2 *)(iVar4 + 8) = 0xffff;
                *(undefined2 *)(iVar4 + 10) = 0x32;
                *(undefined2 *)(iVar4 + 0xc) = 1;
                score = score + 200;
                sky_flash_color = 0xf00;
                break;
              }
            }
            iVar4 = iVar4 + 0xe;
          }
        }
      }
    }
  }
  else {
    if (DAT_00027672 == 0) {
      sky_flash_count = 5;
      sky_flash_color = 0xfff;
    }
    if (uVar2 != 0x113) {
      if (uVar2 == 3) {
        cVar7 = find_ground_object_record();
        if (-1 < cVar7) {
          if (DAT_00027672 == 0) {
            sky_flash_color = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            score = score + 200;
            empty_building_soldiers();
          }
        }
      }
      else if (uVar2 == 4) {
        find_object_anchor_cells();
        iVar4 = DAT_00024578;
        uVar6 = *(ushort *)(DAT_00024578 + extraout_A0w);
        *(undefined2 *)(DAT_00024578 + extraout_A0w) = 0x16;
        *(ushort *)(iVar4 + extraout_A0w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + extraout_A0w);
        uVar6 = *(ushort *)(iVar4 + extraout_A1w);
        *(undefined2 *)(iVar4 + extraout_A1w) = 0x16;
        *(ushort *)(iVar4 + extraout_A1w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + extraout_A1w);
        uVar6 = *(ushort *)(iVar4 + unaff_A2w);
        *(undefined2 *)(iVar4 + unaff_A2w) = 0x16;
        *(ushort *)(iVar4 + unaff_A2w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + unaff_A2w);
        uVar6 = *(ushort *)(iVar4 + unaff_A3w);
        *(undefined2 *)(iVar4 + unaff_A3w) = 0x16;
        *(ushort *)(iVar4 + unaff_A3w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + unaff_A3w);
        iVar4 = find_ground_object_record();
        if (-1 < iVar4) {
          if (DAT_00027672 == 0) {
            sky_flash_color = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          score = score + 0x96;
          empty_building_soldiers();
        }
      }
      else if ((((0xe < uVar2) && (uVar2 < 0x1e)) && (DAT_00027672 == 0)) &&
              (cVar7 = find_ground_object_record(), -1 < cVar7)) {
        sky_flash_color = 0xf00;
        sVar8 = *extraout_A0_01;
        find_object_anchor_cells();
        iVar4 = DAT_00024578;
        sVar8 = (1 << (4U - (((short)((uVar6 & 0x3fff) - sVar8) >> 1) + 3) & 0x3f) | uVar2 - 0xf) +
                0xf;
        *(ushort *)(DAT_00024578 + extraout_A0w_00) =
             *(ushort *)(DAT_00024578 + extraout_A0w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar4 + extraout_A1w_00) =
             *(ushort *)(iVar4 + extraout_A1w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar4 + unaff_A2w) = *(ushort *)(iVar4 + unaff_A2w) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar4 + unaff_A3w) = *(ushort *)(iVar4 + unaff_A3w) & 0x8000 | sVar8 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar8 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          score = score + 200;
          psVar1 = (short *)((int)&island_enemy_counts + (short)(sVar8 * 4) + 2);
          sVar3 = *psVar1 + -1;
          *psVar1 = sVar3;
          if ((sVar3 == 0) && (*(short *)((int)&island_enemy_counts + (int)(short)(sVar8 * 4)) == 0)
             ) {
            uVar6 = get_island_bonus();
            uVar9 = (uint)uVar6;
            score = uVar9 + score;
            bVar10 = SBORROW1(enemy_islands_remaining,'\x01');
            enemy_islands_remaining = enemy_islands_remaining - 1;
            if ((enemy_islands_remaining == 0 ||
                 bVar10 != (int)((uint)enemy_islands_remaining << 0x18) < 0) &&
               (ships_remaining == '\0')) {
              (*_format_string)();
              (*_advance_mission)(uVar9);
            }
            else {
              (*_ticker_printf)(uVar9);
            }
          }
        }
      }
    }
  }
  return CONCAT44(CONCAT22((short)((uint)param_1 >> 0x10),sVar5),in_D1);
}


// ==== weapon_impact_ground_objects @ 000146dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 weapon_impact_ground_objects(void)

{
  short *psVar1;
  short sVar2;
  undefined4 in_D0;
  char cVar5;
  int iVar3;
  ushort uVar4;
  undefined4 in_D1;
  ushort extraout_D1w;
  short sVar6;
  ushort uVar7;
  uint uVar8;
  ushort *in_A0;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  bool bVar9;
  
  uVar4 = *in_A0;
  cVar5 = (*_map_cell_at_x)();
  if ((cVar5 == '\0') || (uVar7 = extraout_D1w & 0x1fff, cVar5 == '\x01')) {
    iVar3 = find_ship_at_x();
    if ((-1 < iVar3) && (in_A0[0x11] != 1)) {
      if ((in_A0[0x11] == 2) && (sky_flash_count = 5, *(char *)(in_A0 + 0xf) == '\n')) {
        sky_flash_color = 0xf00;
        if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
           (sVar6 = *(short *)(extraout_A0_02 + 0xc) + -1, *(short *)(extraout_A0_02 + 0xc) = sVar6,
           sVar6 == 0)) {
          *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
        }
      }
      else {
        sky_flash_count = 5;
        sky_flash_color = 0xfff;
        iVar3 = *(int *)(extraout_A0_02 + 6);
        if (iVar3 != 0) {
          sVar6 = *(short *)(extraout_A0_02 + 10);
          while (sVar6 = sVar6 + -1, sVar6 != -1) {
            if (*(short *)(iVar3 + 8) == 0) {
              uVar7 = uVar4 - *(short *)(iVar3 + 4);
              if ((int)((uint)uVar7 << 0x10) < 0) {
                uVar7 = -uVar7;
              }
              if ((short)uVar7 < 0x10) {
                *(undefined2 *)(iVar3 + 8) = 0xffff;
                *(undefined2 *)(iVar3 + 10) = 0x32;
                *(undefined2 *)(iVar3 + 0xc) = 1;
                score = score + 200;
                sky_flash_color = 0xf00;
                break;
              }
            }
            iVar3 = iVar3 + 0xe;
          }
        }
      }
    }
  }
  else {
    if (in_A0[0x11] == 0) {
      sky_flash_count = 5;
      sky_flash_color = 0xfff;
    }
    if (uVar7 != 0x113) {
      if (uVar7 == 3) {
        cVar5 = find_ground_object_record();
        if (-1 < cVar5) {
          if (in_A0[0x11] == 0) {
            sky_flash_color = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            score = score + 200;
            empty_building_soldiers();
          }
        }
      }
      else if (uVar7 == 4) {
        find_object_anchor_cells();
        iVar3 = DAT_00024578;
        uVar4 = *(ushort *)(DAT_00024578 + extraout_A0w);
        *(undefined2 *)(DAT_00024578 + extraout_A0w) = 0x16;
        *(ushort *)(iVar3 + extraout_A0w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + extraout_A0w);
        uVar4 = *(ushort *)(iVar3 + extraout_A1w);
        *(undefined2 *)(iVar3 + extraout_A1w) = 0x16;
        *(ushort *)(iVar3 + extraout_A1w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + extraout_A1w);
        uVar4 = *(ushort *)(iVar3 + unaff_A2w);
        *(undefined2 *)(iVar3 + unaff_A2w) = 0x16;
        *(ushort *)(iVar3 + unaff_A2w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + unaff_A2w);
        uVar4 = *(ushort *)(iVar3 + unaff_A3w);
        *(undefined2 *)(iVar3 + unaff_A3w) = 0x16;
        *(ushort *)(iVar3 + unaff_A3w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + unaff_A3w);
        iVar3 = find_ground_object_record();
        if (-1 < iVar3) {
          if (in_A0[0x11] == 0) {
            sky_flash_color = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          score = score + 0x96;
          empty_building_soldiers();
        }
      }
      else if ((((0xe < uVar7) && (uVar7 < 0x1e)) && (in_A0[0x11] == 0)) &&
              (cVar5 = find_ground_object_record(), -1 < cVar5)) {
        sky_flash_color = 0xf00;
        sVar6 = *extraout_A0_01;
        find_object_anchor_cells();
        iVar3 = DAT_00024578;
        sVar6 = (1 << (4U - (((short)((uVar4 >> 2) - sVar6) >> 1) + 3) & 0x3f) | uVar7 - 0xf) + 0xf;
        *(ushort *)(DAT_00024578 + extraout_A0w_00) =
             *(ushort *)(DAT_00024578 + extraout_A0w_00) & 0x8000 | sVar6 * 4 | 2U;
        *(ushort *)(iVar3 + extraout_A1w_00) =
             *(ushort *)(iVar3 + extraout_A1w_00) & 0x8000 | sVar6 * 4 | 2U;
        *(ushort *)(iVar3 + unaff_A2w) = *(ushort *)(iVar3 + unaff_A2w) & 0x8000 | sVar6 * 4 | 2U;
        *(ushort *)(iVar3 + unaff_A3w) = *(ushort *)(iVar3 + unaff_A3w) & 0x8000 | sVar6 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar6 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          score = score + 200;
          psVar1 = (short *)((int)&island_enemy_counts + (short)(sVar6 * 4) + 2);
          sVar2 = *psVar1 + -1;
          *psVar1 = sVar2;
          if ((sVar2 == 0) && (*(short *)((int)&island_enemy_counts + (int)(short)(sVar6 * 4)) == 0)
             ) {
            uVar4 = get_island_bonus();
            uVar8 = (uint)uVar4;
            score = uVar8 + score;
            bVar9 = SBORROW1(enemy_islands_remaining,'\x01');
            enemy_islands_remaining = enemy_islands_remaining - 1;
            if ((enemy_islands_remaining == 0 ||
                 bVar9 != (int)((uint)enemy_islands_remaining << 0x18) < 0) &&
               (ships_remaining == '\0')) {
              (*_format_string)();
              (*_advance_mission)(uVar8);
            }
            else {
              (*_ticker_printf)(uVar8);
            }
          }
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== find_ship_at_x @ 00014a4e ====

short find_ship_at_x(void)

{
  ushort in_D0w;
  short sVar1;
  
  sVar1 = (in_D0w >> 3) * 2;
  if (((((has_destroyer == '\0') || (sVar1 < ship_destroyer)) || (DAT_000253b2 < sVar1)) &&
      ((((has_battleship == '\0' || (sVar1 < ship_battleship)) || (DAT_000253d0 < sVar1)) &&
       (((has_transport == '\0' || (sVar1 < ship_transport)) || (DAT_000253ee < sVar1)))))) &&
     ((((has_jcarrier == '\0' || (sVar1 < ship_jcarrier)) || (DAT_0002540c < sVar1)) &&
      ((sVar1 < ship_own_carrier || (DAT_0002542a < sVar1)))))) {
    sVar1 = -1;
  }
  return sVar1;
}


// ==== find_ship_at_offset @ 00014a52 ====

/* WARNING: Type propagation algorithm not settling */

void find_ship_at_offset(void)

{
  return;
}


// ==== find_object_anchor_cells @ 00014ae4 ====

undefined8 find_object_anchor_cells(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  return CONCAT44(in_D0,in_D1);
}


// ==== empty_building_soldiers @ 00014b40 ====

void empty_building_soldiers(void)

{
  int in_A0;
  
  *(char *)(in_A0 + 10) = *(char *)(in_A0 + 8) + *(char *)(in_A0 + 10);
  *(undefined1 *)(in_A0 + 8) = 0;
  *(undefined1 *)(in_A0 + 0xb) = 0x3c;
  return;
}


// ==== find_ground_object_record @ 00014b54 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 find_ground_object_record(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 in_D1;
  ushort extraout_D1w;
  ushort uVar3;
  int extraout_A0;
  int extraout_A1;
  int *piVar4;
  short *psVar5;
  int unaff_A2;
  int unaff_A3;
  
  find_object_anchor_cells();
  iVar2 = extraout_A0;
  if (((((*(byte *)(DAT_00024578 + (short)extraout_A0) & 0x80) == 0) &&
       (iVar2 = extraout_A1, (*(byte *)(DAT_00024578 + (short)extraout_A1) & 0x80) == 0)) &&
      (iVar2 = unaff_A2, (*(byte *)(DAT_00024578 + (short)unaff_A2) & 0x80) == 0)) &&
     (iVar2 = unaff_A3, (*(byte *)(DAT_00024578 + (short)unaff_A3) & 0x80) == 0)) {
    uVar1 = 0xffffffff;
  }
  else {
    (*_map_cell_at_x)();
    uVar3 = extraout_D1w & 0x1fff;
    if (uVar3 == 5) {
      uVar1 = 0;
      uVar3 = (ushort)hut_count;
      piVar4 = huts_ptr;
      do {
        if (iVar2 == *piVar4) goto LAB_00014c34;
        piVar4 = piVar4 + 4;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0xffff);
      uVar1 = 0xffffffff;
    }
    else if (uVar3 == 3) {
      uVar1 = 0;
      uVar3 = (ushort)bunker_count;
      piVar4 = bunkers_ptr;
      do {
        if (iVar2 == *piVar4) goto LAB_00014c34;
        piVar4 = piVar4 + 4;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0xffff);
      uVar1 = 0xffffffff;
    }
    else if ((uVar3 < 0xf) || ('\x1e' < (char)uVar3)) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = 0;
      uVar3 = (ushort)pillbox_count;
      psVar5 = pillboxes_ptr;
      do {
        if ((short)iVar2 == *psVar5) goto LAB_00014c34;
        psVar5 = psVar5 + 7;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0xffff);
      uVar1 = 0xffffffff;
    }
  }
LAB_00014c34:
  return CONCAT44(uVar1,in_D1);
}


// ==== update_ship_guns @ 00014c3e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 update_ship_guns(void)

{
  undefined2 *puVar1;
  short sVar2;
  undefined4 in_D0;
  short sVar4;
  uint uVar3;
  undefined4 in_D1;
  short sVar5;
  int extraout_A1;
  int extraout_A1_00;
  int extraout_A1_01;
  int iVar6;
  undefined **ppuVar7;
  undefined **ppuVar8;
  
  if (player_state == 0) {
    ppuVar7 = &ship_ptr_list;
    while( true ) {
      ppuVar8 = ppuVar7 + 1;
      puVar1 = (undefined2 *)*ppuVar7;
      if ((int)puVar1 < 0) break;
      ppuVar7 = ppuVar8;
      if (((puVar1 != &ship_own_carrier) && (puVar1[2] != 0)) && (0 < (short)puVar1[6])) {
        sVar5 = puVar1[5];
        iVar6 = *(int *)(puVar1 + 3);
        while (sVar5 = sVar5 + -1, sVar5 != -1) {
          if (*(short *)(iVar6 + 8) == 0) {
            ship_gun_splash_torpedo_check();
            sVar4 = aa_gun_aim_lookup();
            iVar6 = extraout_A1;
            if (-1 < sVar4) {
              (*_thunk_FUN_000203be)();
              if ((view_scale != 1) || (uVar3 = (*_thunk_FUN_000203be)(), (uVar3 & 0x8000) == 0)) {
                (*_draw_world_object)();
              }
              aa_gun_hit_roll();
              iVar6 = extraout_A1_00;
            }
          }
          else if (((*(short *)(iVar6 + 10) != 0) &&
                   (sVar4 = *(short *)(iVar6 + 0xc), sVar2 = sVar4 + -1,
                   *(short *)(iVar6 + 0xc) = sVar2, sVar2 == 0 || sVar4 < 1)) &&
                  (sVar4 = *(short *)(iVar6 + 10) + -1, *(short *)(iVar6 + 10) = sVar4, sVar4 != 0))
          {
            *(short *)(iVar6 + 0xc) = 0x32 - *(short *)(iVar6 + 10);
            (*_spawn_smoke_particle)();
            iVar6 = extraout_A1_01;
          }
          iVar6 = iVar6 + 0xe;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== aa_gun_aim_frame @ 00014d50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 aa_gun_aim_frame(void)

{
  undefined2 uVar1;
  undefined4 in_D0;
  uint uVar2;
  undefined4 uVar3;
  short sVar4;
  undefined4 in_D1;
  short sVar5;
  
  uVar1 = (undefined2)((uint)in_D0 >> 0x10);
  sVar5 = -1;
  if (player_state == 0) {
    if (zoom_shift != 0) {
      uVar2 = (*_thunk_FUN_000203be)();
      if ((uVar2 & 0x8000) == 0) {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = CONCAT22((short)(uVar2 >> 0x10),0x5a);
      }
      goto LAB_00014db2;
    }
    uVar3 = aa_gun_aim_lookup();
    sVar4 = (short)uVar3;
    if (sVar4 < 0) goto LAB_00014db2;
    sVar5 = sVar4 + 0x81;
    uVar3 = (*_thunk_FUN_000203be)();
    uVar1 = (undefined2)((uint)uVar3 >> 0x10);
    if ((ushort)((ushort)uVar3 >> 0xc) < 6) {
      sVar5 = sVar4 + 0x88;
    }
  }
  uVar3 = CONCAT22(uVar1,sVar5);
LAB_00014db2:
  return CONCAT44(uVar3,in_D1);
}


// ==== aa_gun_aim_lookup @ 00014db8 ====

void aa_gun_aim_lookup(void)

{
  return;
}


// ==== hut_smoke @ 00014e18 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 hut_smoke(void)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  undefined4 in_D0;
  ushort uVar5;
  uint uVar4;
  undefined4 in_D1;
  short unaff_D4w;
  int *piVar6;
  
  if (view_scale == 1) {
    uVar3 = (undefined2)((uint)in_D0 >> 0x10);
    uVar5 = (unaff_D4w * 8 + (render_player_x & 0xfff8)) - 0x538;
  }
  else {
    uVar5 = unaff_D4w + (render_player_x - 0xa0);
    uVar3 = 0;
  }
  uVar4 = CONCAT22(uVar3,uVar5 >> 2) & 0xfffffffe;
  for (piVar6 = huts_ptr; CONCAT22((short)(uVar4 >> 0x10),(short)uVar4 + -2) != *piVar6;
      piVar6 = piVar6 + 4) {
  }
  if (((*(short *)(piVar6 + 3) != 0) &&
      (sVar1 = *(short *)((int)piVar6 + 0xe), sVar2 = sVar1 + -1,
      *(short *)((int)piVar6 + 0xe) = sVar2, sVar2 == 0 || sVar1 < 1)) &&
     (sVar1 = *(short *)(piVar6 + 3) + -1, *(short *)(piVar6 + 3) = sVar1, sVar1 != 0)) {
    *(short *)((int)piVar6 + 0xe) = 0x32 - *(short *)(piVar6 + 3);
    (*_spawn_smoke_particle)();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014eac @ 00014eac ====

undefined4 FUN_00014eac(void)

{
  undefined4 in_D0;
  
  find_ship_at_x();
  return in_D0;
}


// ==== ship_gun_splash_torpedo_check @ 00014efc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 ship_gun_splash_torpedo_check(void)

{
  undefined4 in_D0;
  ushort uVar1;
  ushort uVar2;
  undefined4 in_D1;
  
  uVar2 = (short)in_D0 - player_x;
  if ((short)uVar2 < 0) {
    uVar2 = -uVar2;
  }
  uVar1 = (*_thunk_FUN_000203be)();
  if ((uVar2 < (uVar1 & 0x1ff)) && (DAT_00026c9a = 0xff, player_y < 0xc9)) {
    uVar2 = (*_thunk_FUN_000203be)();
    if ((short)((uVar2 & 0xf) - 6) < 0) {
      (*_thunk_FUN_000203be)();
      (*_add_gun_impact)();
      destroy_torpedoes_near();
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== aa_gun_hit_roll @ 00014f5c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 aa_gun_hit_roll(void)

{
  bool bVar1;
  short sVar2;
  undefined4 in_D0;
  ushort uVar3;
  ushort uVar4;
  undefined4 in_D1;
  ushort uVar5;
  
  uVar4 = (short)in_D0 - render_player_x;
  if ((short)uVar4 < 0) {
    uVar4 = -uVar4;
  }
  if ((short)uVar4 < 0x1c1) {
    if ((short)uVar4 <= (short)aa_nearest_dist) {
      aa_nearest_dist = uVar4;
    }
    uVar5 = player_y;
    if ((short)uVar4 <= (short)player_y) {
      uVar5 = uVar4;
      uVar4 = player_y;
    }
    aa_firing_flag._0_1_ = 0xff;
    if (invulnerable == 0) {
      uVar3 = (*_thunk_FUN_000203be)();
      if ((short)((uVar5 >> 2) + uVar4) <= (short)(uVar3 & 0x1ff)) {
        uVar4 = (*_thunk_FUN_000203be)();
        if ((uVar4 & 0x7ff) < 0x19a) {
          spawn_player_smoke();
          sVar2 = player_flak_counter + -1;
          bVar1 = player_flak_counter < 1;
          player_flak_counter = sVar2;
          if (sVar2 == 0 || bVar1) {
            player_oil = player_oil + -1;
            uVar4 = (*_thunk_FUN_000203be)();
            player_fuel = player_fuel - (uVar4 & 3);
            uVar4 = (*_thunk_FUN_000203be)();
            player_flak_counter = (uVar4 & 7) + 6;
          }
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== send_soldier_to_empty_bunker @ 00014fee ====

/* WARNING: Removing unreachable block (ram,0x00015010) */
/* WARNING: Removing unreachable block (ram,0x0001501e) */
/* WARNING: Removing unreachable block (ram,0x00015020) */

undefined4 send_soldier_to_empty_bunker(void)

{
  undefined4 in_D0;
  
  find_nearest_manned_hut();
  return in_D0;
}


// ==== find_nearest_manned_hut @ 00015034 ====

void find_nearest_manned_hut(void)

{
  short sVar1;
  short unaff_D2w;
  short unaff_D7w;
  short sVar2;
  int in_A0;
  int in_A1;
  
  sVar2 = unaff_D7w + -1;
  do {
    if (*(char *)(in_A0 + 9) < *(char *)(in_A1 + 9)) {
      return;
    }
    if ((*(char *)(in_A0 + 9) == *(char *)(in_A1 + 9)) && ('\x01' < *(char *)(in_A1 + 8))) {
      sVar1 = *(short *)(in_A0 + 4) - *(short *)(in_A1 + 4);
      if (sVar1 != 0) {
        if (sVar1 < 0) {
          sVar1 = -sVar1;
        }
        if (sVar1 <= unaff_D2w) {
          unaff_D2w = sVar1;
        }
      }
    }
    in_A1 = in_A1 + 0x10;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}


// ==== FUN_00015076 @ 00015076 ====

void FUN_00015076(void)

{
  return;
}


// ==== format_string @ 00015078 ====

undefined4 format_string(void)

{
  undefined4 in_D0;
  
  (**(code **)(DAT_00026ec4 + -0x20a))();
  return in_D0;
}


// ==== FUN_00015094 @ 00015094 ====

undefined4 FUN_00015094(void)

{
  undefined4 in_D0;
  
  (**(code **)(DAT_00026ec4 + -0x20a))();
  return in_D0;
}


// ==== present_frame @ 000150b0 ====

undefined8 present_frame(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  flip_views(back_view);
  FUN_0001520c();
  return CONCAT44(in_D0,in_D1);
}


// ==== map_cell_at_x @ 000150c8 ====

ulonglong map_cell_at_x(void)

{
  undefined4 in_D0;
  ushort uVar1;
  undefined4 in_D1;
  
  uVar1 = (ushort)in_D0;
  if ((-1 < (short)uVar1) && (uVar1 < DAT_00024580)) {
    uVar1 = *(ushort *)(DAT_00024578 + (short)((uVar1 >> 3) * 2));
    return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),uVar1),
                    CONCAT22((short)((uint)in_D1 >> 0x10),uVar1 >> 2)) & 0xffff0003ffff01ff;
  }
  return 0;
}


// ==== FUN_00015102 @ 00015102 ====

void FUN_00015102(void)

{
  return;
}


// ==== cos_lookup @ 00015104 ====

short cos_lookup(void)

{
  short in_D0w;
  ushort uVar1;
  ushort uVar2;
  
  uVar2 = in_D0w + 0x100U & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(&DAT_000248bc + (short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(&DAT_000248bc + (short)(uVar2 * 2));
}


// ==== sin_lookup @ 00015108 ====

short sin_lookup(void)

{
  ushort in_D0w;
  ushort uVar1;
  ushort uVar2;
  
  uVar2 = in_D0w & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(&DAT_000248bc + (short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(&DAT_000248bc + (short)(uVar2 * 2));
}


// ==== tan_lookup @ 0001514c ====

undefined6 tan_lookup(void)

{
  ushort in_D0w;
  ushort uVar1;
  short sVar2;
  undefined4 in_D1;
  
  uVar1 = in_D0w;
  if ((short)in_D0w < 0) {
    uVar1 = -in_D0w;
  }
  sVar2 = *(short *)(&DAT_000246bc + (short)((uVar1 & 0xff) * 2));
  if ((short)in_D0w < 0) {
    sVar2 = -sVar2;
  }
  return CONCAT24(sVar2,in_D1);
}


// ==== draw_world_object @ 00015174 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_world_object(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  
  sVar1 = (short)in_D0 - camera_left_x;
  if (zoom_shift != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (*_draw_shape_automask)();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== draw_world_object_xor @ 000151c2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_world_object_xor(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  
  sVar1 = (short)in_D0 - camera_left_x;
  if (zoom_shift != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (*_blit_shape_xor)();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001520c @ 0001520c ====

void FUN_0001520c(void)

{
  return;
}


// ==== read_joystick_dirs @ 0001520e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined6 read_joystick_dirs(void)

{
  ushort uVar1;
  undefined4 in_D1;
  
  uVar1 = (ushort)(byte)(&DAT_000255f6)[(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3)];
  if ((((&DAT_000255f6)[(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3)] & 3) != 0) &&
     (invert_updown != '\0')) {
    uVar1 = uVar1 ^ 3;
  }
  return CONCAT24(uVar1,in_D1);
}


// ==== clip_playfield @ 0001524a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void clip_playfield(void)

{
  (*_set_clip_rect)();
  return;
}


// ==== clip_3d_view @ 0001525c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void clip_3d_view(void)

{
  (*_set_clip_rect)();
  return;
}


// ==== clip_to_deck @ 0001526e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 clip_to_deck(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_set_clip_rect)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000152ac @ 000152ac ====

undefined2 FUN_000152ac(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  
  sVar2 = 0x14;
  puVar3 = gun_impacts_ptr;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return param_1._0_2_;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = param_1._0_2_;
  cVar1 = map_cell_at_x();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return param_1._0_2_;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return param_1._0_2_;
}


// ==== add_gun_impact @ 000152b0 ====

undefined4 add_gun_impact(void)

{
  undefined4 in_D0;
  char cVar1;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  
  sVar2 = 0x14;
  puVar3 = gun_impacts_ptr;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return in_D0;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = (short)in_D0;
  cVar1 = map_cell_at_x();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return in_D0;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return in_D0;
}


// ==== draw_splashes @ 000152f8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_splashes(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  int extraout_A1;
  int iVar2;
  
  (*_own_blitter)();
  sVar1 = 0x14;
  iVar2 = gun_impacts_ptr;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if (*(char *)(iVar2 + 2) != '\0') {
      draw_world_object();
      *(char *)(extraout_A1 + 2) = *(char *)(extraout_A1 + 2) + -1;
      iVar2 = extraout_A1;
    }
    iVar2 = iVar2 + 4;
  }
  (*_wait_disown_blitter)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001535a @ 0001535a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001535a(void)

{
  undefined4 in_D0;
  short sVar2;
  undefined4 uVar1;
  undefined4 in_D1;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  sVar2 = 0xb7;
  puVar3 = world_frames;
  puVar5 = cell_frames_eighth;
  puVar7 = eighth_frames;
  puVar6 = cell_frames;
  do {
    puVar8 = puVar6;
    puVar4 = puVar5;
    puVar6 = puVar8 + 1;
    *puVar8 = *puVar3;
    puVar5 = puVar4 + 1;
    *puVar4 = *puVar7;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
    puVar7 = puVar7 + 1;
  } while (sVar2 != -1);
  sVar2 = 0x17;
  puVar3 = DAT_00026ea0;
  if (DAT_00026ea0 == (undefined4 *)0x0) {
    puVar8 = puVar8 + 2;
    *puVar6 = 0;
    puVar4 = puVar4 + 2;
    *puVar5 = 0;
  }
  else {
    do {
      puVar8 = puVar6 + 1;
      *puVar6 = *puVar3;
      uVar1 = (*_find_shape_by_name)();
      puVar4 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar4;
      puVar6 = puVar8;
    } while (sVar2 != -1);
  }
  sVar2 = 0x1a;
  puVar3 = DAT_00026e98;
  if (DAT_00026e98 == (undefined4 *)0x0) {
    puVar7 = puVar8 + 1;
    *puVar8 = 0;
    puVar5 = puVar4 + 1;
    *puVar4 = 0;
  }
  else {
    do {
      puVar7 = puVar8 + 1;
      *puVar8 = *puVar3;
      uVar1 = (*_find_shape_by_name)();
      puVar5 = puVar4 + 1;
      *puVar4 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar4 = puVar5;
      puVar8 = puVar7;
    } while (sVar2 != -1);
  }
  sVar2 = 0xc;
  puVar3 = DAT_00026e90;
  if (has_jcarrier == '\0') {
    puVar4 = puVar7 + 1;
    *puVar7 = 0;
    puVar6 = puVar5 + 1;
    *puVar5 = 0;
  }
  else {
    do {
      puVar4 = puVar7 + 1;
      *puVar7 = *puVar3;
      uVar1 = (*_find_shape_by_name)();
      puVar6 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar6;
      puVar7 = puVar4;
    } while (sVar2 != -1);
  }
  sVar2 = 0x18;
  puVar3 = DAT_00026e88;
  if (DAT_00026e88 == (undefined4 *)0x0) {
    *puVar4 = 0;
    *puVar6 = 0;
  }
  else {
    do {
      *puVar4 = *puVar3;
      uVar1 = (*_find_shape_by_name)();
      *puVar6 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
      puVar4 = puVar4 + 1;
    } while (sVar2 != -1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== spawn_smoke_particle @ 00015460 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void spawn_smoke_particle(void)

{
  undefined4 in_D0;
  uint uVar1;
  int in_D1;
  undefined2 unaff_D2w;
  short sVar2;
  undefined4 *puVar3;
  int extraout_A0;
  int extraout_A0_00;
  
  sVar2 = 0x27;
  puVar3 = smoke_particles_ptr;
  do {
    if (*(short *)(puVar3 + 4) == 0) {
      *puVar3 = in_D0;
      if (in_D1 < 0x100000) {
        in_D1 = 0x100000;
      }
      puVar3[1] = in_D1;
      *(undefined2 *)(puVar3 + 4) = unaff_D2w;
      *(undefined2 *)((int)puVar3 + 0x12) = 6;
      uVar1 = (*_thunk_FUN_000203be)();
      *(uint *)(extraout_A0 + 8) = (uVar1 & 0xffff) + 0x10000;
      uVar1 = (*_thunk_FUN_000203be)();
      *(uint *)(extraout_A0_00 + 0xc) = (uVar1 & 0xffff) + 0x10000;
      return;
    }
    puVar3 = puVar3 + 5;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}


// ==== FUN_000154cc @ 000154cc ====

void FUN_000154cc(void)

{
  spawn_smoke_particle();
  return;
}


// ==== spawn_player_smoke @ 000154e0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 spawn_player_smoke(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  spawn_smoke_particle();
  return CONCAT44(in_D0,in_D1);
}


// ==== ticker_start_message @ 0001555a ====

undefined4 ticker_start_message(void)

{
  undefined4 in_A0;
  
  if (ticker_message == 0) {
    ticker_message = in_A0;
    return 0;
  }
  return 0xffffffff;
}


// ==== FUN_0001556e @ 0001556e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001556e(void)

{
  if (DAT_00024bfc != 0) {
                    /* WARNING: Could not recover jumptable at 0x00015576. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*_thunk_FUN_00021dce)();
    return;
  }
  return;
}


// ==== draw_balloons @ 0001557c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_balloons(void)

{
  ushort uVar2;
  char cVar3;
  uint uVar1;
  char cVar4;
  short *psVar5;
  
  psVar5 = confetti_particles_ptr;
  if ((victory_balloons != '\0') && (view_scale == 8)) {
    cVar4 = '\0';
    (*_own_blitter)();
    do {
      if (*(char *)((int)psVar5 + 0x11) == '\0') {
        *psVar5 = carrier_home_x;
        *psVar5 = *psVar5 + -0x74;
        psVar5[2] = 0x38;
        uVar2 = (*_thunk_FUN_000203be)();
        uVar2 = uVar2 >> 0xc & 3;
        cVar3 = (char)uVar2;
        if (uVar2 == 0) {
          cVar3 = '\x02';
        }
        *(char *)(psVar5 + 8) = cVar3 + -1;
        uVar1 = (*_thunk_FUN_000203be)();
        *(uint *)(psVar5 + 4) = (uVar1 & 0xffff) * 2 + 0x10000;
        uVar1 = (*_thunk_FUN_000203be)();
        *(uint *)(psVar5 + 6) = (uVar1 & 0xffff) * 2 + 0x10000;
        *(undefined1 *)((int)psVar5 + 0x11) = 0xff;
      }
      draw_world_object();
      psVar5 = psVar5 + 9;
      cVar4 = cVar4 + '\x01';
    } while (cVar4 != '\x14');
    (*_wait_disown_blitter)();
  }
  return;
}


// ==== ticker_printf @ 00015624 ====

void ticker_printf(void)

{
  format_string();
  ticker_start_message();
  return;
}


// ==== show_ship_sunk_message @ 00015640 ====

void show_ship_sunk_message(void)

{
  undefined **ppuVar1;
  int in_A1;
  
  if (*(short *)(in_A1 + 0x12) != 0) {
    ppuVar1 = &PTR_s_Battleship_00023af8;
    if (((*(short *)(in_A1 + 0x12) != 0x1194) &&
        (ppuVar1 = &PTR_s_Carrier_00023afc, *(short *)(in_A1 + 0x12) != 6000)) &&
       (ppuVar1 = &PTR_s_Destroyer_00023b00, *(short *)(in_A1 + 0x12) != 0x9c4)) {
      ppuVar1 = &PTR_s_Cruiser_00023b04;
    }
    format_string(*ppuVar1,(int)*(short *)(in_A1 + 0x12));
  }
  return;
}


// ==== advance_mission @ 00015694 ====

undefined4 advance_mission(void)

{
  char cVar1;
  undefined4 in_D0;
  char *pcVar2;
  
  mission_in_rank = mission_in_rank + 1;
  if (*(short *)((int)&missions_per_rank + (int)(short)(rank * 2)) < mission_in_rank) {
    mission_in_rank = 1;
    rank = rank + 1;
    if (6 < rank) {
      rank = 6;
    }
    victory_balloons = 0xff;
    pcVar2 = &message_buffer;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    format_string();
  }
  else {
    pcVar2 = &message_buffer;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    format_string();
  }
  ticker_message = &message_buffer;
  mission_complete = 0xffff;
  return in_D0;
}


// ==== object_height @ 00015710 ====

short object_height(ushort *param_1)

{
  ushort uVar1;
  short sVar2;
  undefined2 *puVar3;
  
  uVar1 = *param_1 >> 2 & 0x1ff;
  sVar2 = 0;
  if (((((uVar1 == 6) || (sVar2 = 1, uVar1 == 7)) || (sVar2 = 2, uVar1 == 8)) ||
      ((uVar1 == 0xb || (sVar2 = 3, uVar1 == 3)))) || (sVar2 = 4, uVar1 == 4)) {
LAB_00015878:
    sVar2 = *(short *)((int)&DAT_00025712 + (int)(short)(sVar2 * 2)) - (*param_1 >> 0xb & 7);
  }
  else {
    sVar2 = 5;
    if (0xe < uVar1) {
      if (uVar1 < 0x1f) goto LAB_00015878;
      puVar3 = &ship_transport;
      if ((((((uVar1 == 0xcc) || (puVar3 = &ship_jcarrier, uVar1 == 0xf1)) ||
            ((uVar1 == 0xf3 ||
             (((uVar1 == 0xf2 || (uVar1 == 0xf6)) || (puVar3 = &ship_battleship, uVar1 == 0x10c)))))
            ) || ((uVar1 == 0x10e || (uVar1 == 0x10d)))) || (uVar1 == 0x10f)) ||
         (((uVar1 == 0x110 || (puVar3 = &ship_destroyer, uVar1 == 0xe5)) ||
          ((uVar1 == 0xe6 || ((uVar1 == 0xe4 || (uVar1 == 0xe7)))))))) {
        return (puVar3[7] - puVar3[10]) - wave_bob;
      }
      if (((((uVar1 == 0x20) || (uVar1 == 0x1f)) || (uVar1 == 0x21)) ||
          ((uVar1 == 0x26 || (uVar1 == 0x23)))) ||
         (((uVar1 == 0x22 || ((uVar1 == 0x24 || (uVar1 == 0x25)))) ||
          ((uVar1 == 0x9f || (uVar1 == 0x27)))))) {
        return ((carrier_deck_base_height - DAT_0002543c) - wave_bob) - elevator_offset;
      }
    }
    sVar2 = 0;
  }
  return sVar2;
}


// ==== object_height_at_cell_a0 @ 00015714 ====

short object_height_at_cell_a0(void)

{
  ushort uVar1;
  short sVar2;
  ushort *in_A0;
  undefined2 *puVar3;
  
  uVar1 = *in_A0 >> 2 & 0x1ff;
  sVar2 = 0;
  if (((((uVar1 == 6) || (sVar2 = 1, uVar1 == 7)) || (sVar2 = 2, uVar1 == 8)) ||
      ((uVar1 == 0xb || (sVar2 = 3, uVar1 == 3)))) || (sVar2 = 4, uVar1 == 4)) {
LAB_00015878:
    sVar2 = *(short *)((int)&DAT_00025712 + (int)(short)(sVar2 * 2)) - (*in_A0 >> 0xb & 7);
  }
  else {
    sVar2 = 5;
    if (0xe < uVar1) {
      if (uVar1 < 0x1f) goto LAB_00015878;
      puVar3 = &ship_transport;
      if ((((((uVar1 == 0xcc) || (puVar3 = &ship_jcarrier, uVar1 == 0xf1)) ||
            ((uVar1 == 0xf3 ||
             (((uVar1 == 0xf2 || (uVar1 == 0xf6)) || (puVar3 = &ship_battleship, uVar1 == 0x10c)))))
            ) || ((uVar1 == 0x10e || (uVar1 == 0x10d)))) || (uVar1 == 0x10f)) ||
         (((uVar1 == 0x110 || (puVar3 = &ship_destroyer, uVar1 == 0xe5)) ||
          ((uVar1 == 0xe6 || ((uVar1 == 0xe4 || (uVar1 == 0xe7)))))))) {
        return (puVar3[7] - puVar3[10]) - wave_bob;
      }
      if (((((uVar1 == 0x20) || (uVar1 == 0x1f)) || (uVar1 == 0x21)) ||
          ((uVar1 == 0x26 || (uVar1 == 0x23)))) ||
         (((uVar1 == 0x22 || ((uVar1 == 0x24 || (uVar1 == 0x25)))) ||
          ((uVar1 == 0x9f || (uVar1 == 0x27)))))) {
        return ((carrier_deck_base_height - DAT_0002543c) - wave_bob) - elevator_offset;
      }
    }
    sVar2 = 0;
  }
  return sVar2;
}


// ==== ship_index_from_map_ptr @ 00015898 ====

uint ship_index_from_map_ptr(short param_1)

{
  short *psVar1;
  uint uVar2;
  ushort uVar3;
  
  uVar3 = *(ushort *)(DAT_00024578 + (short)(param_1 - (short)DAT_00024578)) & 0xff03;
  if ((char)uVar3 == '\x01') {
    uVar2 = 0;
    while( true ) {
      psVar1 = *(short **)((int)&ship_ptr_list + (int)(short)uVar2);
      if (psVar1 == (short *)0xffffffff) break;
      if (((psVar1[2] != 0) && (*psVar1 <= (short)uVar3)) && ((short)uVar3 <= psVar1[1])) {
        return uVar2;
      }
      uVar2 = (uint)(ushort)((short)uVar2 + 4);
    }
  }
  return 0xffffffff;
}


// ==== alloc_mem @ 000158ec ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void alloc_mem(void)

{
  (*_thunk_FUN_00020848)();
  return;
}


// ==== FUN_000158fe @ 000158fe ====

void FUN_000158fe(void)

{
  FUN_000165cc();
  return;
}


// ==== FUN_00015910 @ 00015910 ====

longlong FUN_00015910(undefined4 param_1,uint param_2)

{
  short sVar1;
  
  sVar1 = FUN_00015956();
  if (sVar1 != 0) {
    (**(code **)(DAT_00026e72 + -0x24))();
  }
  return (ulonglong)param_2 << 0x20;
}


// ==== FUN_0001591e @ 0001591e ====

undefined6 FUN_0001591e(void)

{
  byte bVar1;
  short in_D0w;
  undefined4 in_D1;
  ushort uVar2;
  short sVar3;
  byte *in_A0;
  
  sVar3 = 0;
  do {
    bVar1 = *in_A0;
    if ((bVar1 <= DAT_00026ebf) && (font_first_char <= bVar1)) {
      bVar1 = *(byte *)(ticker_font + 4 + (int)(short)(ushort)(byte)(bVar1 - font_first_char));
      uVar2 = (ushort)bVar1;
      if (bVar1 == 0) {
        uVar2 = 10;
      }
      sVar3 = uVar2 + sVar3 + 1;
    }
    in_D0w = in_D0w + -1;
    in_A0 = in_A0 + 1;
  } while (in_D0w != -1);
  return CONCAT24(sVar3,in_D1);
}


// ==== FUN_00015956 @ 00015956 ====

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined8 FUN_00015956(void)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  undefined4 in_D0;
  ushort uVar6;
  undefined4 in_D1;
  ushort extraout_D1w;
  short unaff_D2w;
  ushort uVar7;
  short unaff_D3w;
  ushort unaff_D4w;
  ushort unaff_D5w;
  short sVar8;
  short sVar9;
  byte *extraout_A0;
  byte *pbVar10;
  undefined2 *extraout_A1;
  ushort *puVar11;
  undefined2 *puVar12;
  uint *puVar13;
  ushort local_3e;
  
  DAT_00027690 = 0;
  local_3e = (short)in_D0 - 1;
  if (0 < (short)in_D0) {
    uVar6 = FUN_0001591e();
    if (DAT_0002768a < uVar6) {
      DAT_0002768a = uVar6;
    }
    if ((uVar6 <= unaff_D4w) && (unaff_D5w <= font_height)) {
      DAT_00027686 = 0;
      DAT_00027688 = 0;
      sVar9 = unaff_D3w - uVar6;
      DAT_00027690 = uVar6;
      if (sVar9 != 0 && (short)uVar6 <= unaff_D3w) {
        DAT_00027690 = sVar9 + uVar6;
        DAT_00027686 = (short)((uint)(int)sVar9 / (uint)local_3e);
        DAT_00027688 = (short)((uint)(int)sVar9 % (uint)local_3e);
      }
      DAT_00027680 = ((ushort)(unaff_D4w + 0xf) >> 4) * 2;
      uVar6 = extraout_D1w & 0xf;
      sVar9 = unaff_D2w * DAT_00027680 + ((short)extraout_D1w >> 4) * 2;
      sVar8 = ((ushort)(unaff_D5w * DAT_00027680) >> 1) - 1;
      puVar12 = extraout_A1;
      do {
        *puVar12 = 0;
        iVar5 = ticker_font;
        iVar4 = font_glyph_data;
        sVar8 = sVar8 + -1;
        pbVar10 = extraout_A0;
        puVar12 = puVar12 + 1;
        DAT_0002768c = extraout_A1;
      } while (sVar8 != -1);
      do {
        bVar1 = *pbVar10;
        if ((bVar1 <= DAT_00026ebf) && (font_first_char <= bVar1)) {
          DAT_00027682 = 10;
          bVar2 = *(byte *)(iVar5 + 4 + (int)(short)(ushort)(byte)(bVar1 - font_first_char));
          if (bVar2 != 0) {
            DAT_00027682 = (ushort)bVar2;
            DAT_00027684 = (ushort)(DAT_00027682 + 0xf) >> 4;
            DAT_0002767e = DAT_00027680 + DAT_00027684 * -2;
            puVar11 = (ushort *)
                      (*(short *)((int)&font_glyph_offsets +
                                 (int)(short)((ushort)(byte)(bVar1 - font_first_char) * 2)) + iVar4)
            ;
            puVar13 = (uint *)((int)sVar9 + (int)DAT_0002768c);
            sVar8 = font_height - 1;
            uVar7 = DAT_00027684;
            do {
              while ((ushort)(uVar7 - 1) != 0xffff) {
                *puVar13 = ((uint)*puVar11 << 0x10) >> uVar6 | *puVar13;
                puVar13 = (uint *)((int)puVar13 + 2);
                puVar11 = puVar11 + 1;
                uVar7 = uVar7 - 1;
              }
              puVar13 = (uint *)((int)DAT_0002767e + (int)puVar13);
              sVar8 = sVar8 + -1;
              uVar7 = DAT_00027684;
            } while (sVar8 != -1);
          }
          uVar7 = DAT_00027686 + DAT_00027682 + uVar6 + 1;
          if (0 < DAT_00027688) {
            uVar7 = uVar7 + 1;
          }
          uVar6 = uVar7 & 0xf;
          sVar9 = (uVar7 >> 4) * 2 + sVar9;
          DAT_00027688 = DAT_00027688 + -1;
        }
        bVar3 = 0 < (short)local_3e;
        pbVar10 = pbVar10 + 1;
        local_3e = local_3e - 1;
      } while (bVar3);
    }
  }
  return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),DAT_00027690),in_D1);
}


// ==== FUN_00015a8c @ 00015a8c ====

undefined8 FUN_00015a8c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  short sVar1;
  
  sVar1 = FUN_00015956();
  if (sVar1 != 0) {
    (**(code **)(DAT_00026e72 + -0x24))();
  }
  return CONCAT44(param_2,param_3);
}


// ==== get_island_bonus @ 00015ae8 ====

undefined6 get_island_bonus(void)

{
  short in_D0w;
  undefined4 in_D1;
  
  return CONCAT24(*(undefined2 *)
                   (&island_bonus_table +
                   (short)(in_D0w * 2 +
                          (ushort)(byte)(&mission_index_table)[(short)(mission_in_rank + rank * 4)]
                          * 8)),in_D1);
}


// ==== FUN_00015b16 @ 00015b16 ====

undefined8 FUN_00015b16(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_D1;
  
  iVar1 = DAT_00026e6e;
  iVar2 = (**(code **)(DAT_00026e6e + -0x1e))();
  uVar3 = 0;
  if (iVar2 != 0) {
    (**(code **)(iVar1 + -0x42))();
    uVar3 = (**(code **)(iVar1 + -0x42))();
    (**(code **)(iVar1 + -0x24))();
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== FUN_00015b1a @ 00015b1a ====

undefined8 FUN_00015b1a(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_D1;
  
  iVar1 = DAT_00026e6e;
  iVar2 = (**(code **)(DAT_00026e6e + -0x1e))();
  uVar3 = 0;
  if (iVar2 != 0) {
    (**(code **)(iVar1 + -0x42))();
    uVar3 = (**(code **)(iVar1 + -0x42))();
    (**(code **)(iVar1 + -0x24))();
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== FUN_00015b58 @ 00015b58 ====

byte FUN_00015b58(ushort *param_1)

{
  ushort uVar1;
  ushort uVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  short sVar7;
  short sVar8;
  ushort *puVar9;
  ushort *puVar10;
  byte *pbVar11;
  
  bVar5 = 0;
  if (param_1 != (ushort *)0x0) {
    uVar1 = *param_1;
    param_1[2] = (uVar1 * 8 + -1) - param_1[2];
    puVar10 = param_1 + 10;
    pbVar11 = (byte *)((int)param_1 + (short)uVar1 + 0x14);
    uVar6 = uVar1 >> 1;
    uVar2 = param_1[1];
    bVar5 = 0;
    param_1 = param_1 + 7;
    cVar3 = *(char *)param_1;
    while (cVar3 != '\0') {
      param_1 = (ushort *)((int)param_1 + 1);
      sVar8 = uVar6 - 1;
      sVar7 = uVar2 - 1;
      do {
        do {
          bVar5 = *(byte *)puVar10;
          pbVar11 = pbVar11 + -1;
          bVar4 = *pbVar11;
          *pbVar11 = (&DAT_00025606)[(short)(ushort)bVar5];
          puVar9 = (ushort *)((int)puVar10 + 1);
          *(undefined *)puVar10 = (&DAT_00025606)[(short)(ushort)bVar4];
          sVar8 = sVar8 + -1;
          puVar10 = puVar9;
        } while (sVar8 != -1);
        pbVar11 = pbVar11 + (short)(uVar6 + uVar1);
        puVar10 = (ushort *)((int)(short)uVar6 + (int)puVar9);
        sVar7 = sVar7 + -1;
        sVar8 = uVar6 - 1;
      } while (sVar7 != -1);
      cVar3 = *(char *)param_1;
    }
  }
  return bVar5;
}


// ==== load_shape_bank @ 00015bc6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong load_shape_bank(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 unaff_D5w;
  undefined4 *puVar3;
  undefined4 in_A0;
  int *in_A1;
  int *piVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  
  piVar4 = in_A1;
  do {
    iVar1 = *piVar4;
    piVar4 = piVar4 + 1;
  } while (iVar1 != 0);
  DAT_000255f2 = in_A0;
  uVar6 = FUN_00015d50();
  uVar2 = (undefined4)uVar6;
  if ((int)((ulonglong)uVar6 >> 0x20) != 0) {
    puVar3 = (undefined4 *)0x0;
    if (in_A1 != (int *)0x0) {
      uVar6 = alloc_mem(unaff_D5w);
      puVar3 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
      uVar2 = (undefined4)uVar6;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        while( true ) {
          puVar5 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
          uVar2 = (undefined4)uVar6;
          if (*in_A1 == 0) break;
          uVar8 = (*_find_shape_by_name)();
          uVar6 = CONCAT44(puVar5 + 1,(int)uVar8);
          *puVar5 = (int)((ulonglong)uVar8 >> 0x20);
          in_A1 = in_A1 + 1;
        }
      }
    }
    return CONCAT44(puVar3,uVar2);
  }
  uVar7 = (**(code **)(DAT_00026e6e + -0x84))();
  (**(code **)(_DAT_00000004 + -0x20a))((int)(uVar7 >> 0x20));
  return uVar7 & 0xffffffff;
}


// ==== FUN_00015c5c @ 00015c5c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_00015c5c(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *in_A1;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)0x0;
  if ((in_A1 != (int *)0x0) && (puVar2 = (undefined4 *)alloc_mem(), puVar2 != (undefined4 *)0x0)) {
    *puVar2 = 0;
    puVar3 = puVar2;
    while (*in_A1 != 0) {
      uVar1 = (*_find_shape_by_name)();
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
      in_A1 = in_A1 + 1;
    }
  }
  return puVar2;
}


// ==== atan2_lookup @ 00015ca6 ====

uint6 atan2_lookup(void)

{
  short in_D0w;
  uint in_D1;
  short sVar1;
  ushort uVar2;
  uint6 uVar3;
  
  sVar1 = (short)in_D1;
  uVar2 = 0;
  if (in_D0w < 0) {
    uVar2 = 0x10;
    in_D0w = -in_D0w;
  }
  if (sVar1 < 0) {
    uVar2 = uVar2 | 8;
    sVar1 = -sVar1;
  }
  if (sVar1 <= in_D0w) {
    if (in_D0w == sVar1) {
      if (in_D0w != 0) {
                    /* WARNING: Could not recover jumptable at 0x00015d0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (**(code **)(&DAT_0002571e + (short)uVar2))();
        return uVar3;
      }
      return (uint6)in_D1;
    }
    uVar2 = uVar2 | 4;
  }
                    /* WARNING: Could not recover jumptable at 0x00015cf6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (**(code **)(&DAT_0002571e + (short)uVar2))();
  return uVar3;
}


// ==== FUN_00015d3e @ 00015d3e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00015d3e(undefined4 param_1)

{
  (*_thunk_FUN_0001feb4)(param_1);
  return;
}


// ==== FUN_00015d4c @ 00015d4c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00015d4c(undefined4 param_1)

{
  (*_thunk_FUN_0001feca)(param_1);
  return;
}


// ==== FUN_00015d50 @ 00015d50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00015d50(void)

{
  (*_thunk_FUN_0001feca)();
  return;
}


// ==== FUN_00015d5a @ 00015d5a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_00015d5a(void)

{
  return _DAT_00dff006;
}


// ==== FUN_00015d62 @ 00015d62 ====

void FUN_00015d62(void)

{
  return;
}


// ==== FUN_00015e1a @ 00015e1a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00015e1a(undefined4 param_1)

{
  undefined4 uVar1;
  
  DAT_00026bb0 = (*_thunk_FUN_00022b30)(param_1,0x3ed);
  if (DAT_00026bb0 == 0) {
    uVar1 = (*_thunk_FUN_00022b06)();
    (*_thunk_FUN_00021dce)(s_Couldn_t_OPEN_file__error___ld_00015e6a,uVar1);
    uVar1 = FUN_00016e96(0);
  }
  else {
    FUN_00015ec2(&LAB_00015d7c,DAT_00026bb0);
    (*_thunk_FUN_00022ab2)(DAT_00026bb0);
    uVar1 = 1;
  }
  return uVar1;
}


// ==== FUN_00015e8a @ 00015e8a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_00015e8a(undefined4 param_1)

{
  bool bVar1;
  
  DAT_00026bb0 = (*_thunk_FUN_00022b30)(param_1,0x3ee);
  bVar1 = DAT_00026bb0 != 0;
  if (bVar1) {
    FUN_00015ec2(&LAB_00015dde,DAT_00026bb0);
    (*_thunk_FUN_00022ab2)(DAT_00026bb0);
  }
  return bVar1;
}


// ==== FUN_00015ec2 @ 00015ec2 ====

void FUN_00015ec2(code *param_1,undefined4 param_2)

{
  undefined2 *local_e;
  short local_a;
  
  (*param_1)(param_2,&projectiles,0x84a);
  (*param_1)(param_2,&DAT_00025316,2);
  (*param_1)(param_2,&DAT_00024578,DAT_00025316);
  DAT_00024580 = DAT_00025316 << 2;
  DAT_0002457c = DAT_00024578 + DAT_00025316;
  local_e = &ship_destroyer;
  local_a = 0;
  do {
    if ((local_e[2] != 0) && (local_e[9] != 0)) {
      (*param_1)(param_2,local_e + 3,local_e[5] * 0xe);
    }
    local_e = local_e + 0xf;
    local_a = local_a + 1;
  } while (local_a < 5);
  FUN_00015d62();
  (*param_1)(param_2,&pillboxes_ptr,pillbox_count * 0xe);
  (*param_1)(param_2,&soldiers_ptr,soldier_slot_count << 3);
  (*param_1)(param_2,&bunkers_ptr,(short)bunker_count << 4);
  (*param_1)(param_2,&huts_ptr,(short)hut_count << 4);
  return;
}


// ==== FUN_00016032 @ 00016032 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016032(undefined4 param_1)

{
  (*_thunk_FUN_00022ec4)(current_rastport,2);
  (*_thunk_FUN_00022e92)
            (current_rastport,(int)param_1._0_2_,(int)param_1._2_2_,param_1._0_2_ + 7,
             param_1._2_2_ + 7);
  (*_thunk_FUN_00022ec4)(current_rastport,1);
  return;
}


// ==== text_input_field @ 00016086 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 text_input_field(undefined1 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  uint uVar1;
  ushort uVar5;
  undefined2 uVar6;
  undefined2 local_68;
  short local_5e;
  undefined1 uStack_5b;
  short local_5a;
  short local_58;
  short local_56;
  undefined1 auStack_54 [80];
  
  local_68 = 0;
  (*_thunk_FUN_00022ea4)((short)current_rastport,6);
  (*_thunk_FUN_00022eb4)((short)current_rastport,0);
  (*_thunk_FUN_00022ec4)((short)current_rastport,1);
  local_5a = 0;
  do {
    auStack_54[local_5a] = 0x20;
    local_5a = local_5a + 1;
  } while (local_5a < 0x50);
  local_58 = -1;
  local_56 = 0;
  while( true ) {
    while( true ) {
      while( true ) {
        if (((local_56 != local_58) && (local_5e == 0)) && (-1 < local_58)) {
          FUN_00016032(param_3._0_2_);
        }
        uVar6 = SUB42(param_1,0);
        if (local_5e != 0) {
          (*_thunk_FUN_00022e78)
                    ((short)current_rastport,param_2._2_2_,
                     param_3._0_2_ + *(short *)(current_rastport + 0x3e));
          uVar2 = (*_thunk_FUN_00021e12)(uVar6);
          (*_thunk_FUN_00022ed4)((short)current_rastport,uVar6,uVar2);
          sVar3 = (*_thunk_FUN_00021e12)(uVar6);
          if (sVar3 <= param_2._0_2_) {
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (*_thunk_FUN_00021e12)(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0;
            sVar3 = (*_thunk_FUN_00021e12)
                              (uVar6,param_3._0_2_ + *(short *)(current_rastport + 0x3e));
            (*_thunk_FUN_00022e78)((short)current_rastport,param_2._2_2_ + sVar3 * 8);
            uVar2 = (*_thunk_FUN_00021e12)((short)auStack_54);
            (*_thunk_FUN_00022ed4)((short)current_rastport,(short)auStack_54,uVar2);
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (*_thunk_FUN_00021e12)(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0x20;
          }
        }
        if ((local_5e != 0) || (local_56 != local_58)) {
          FUN_00016032(param_3._0_2_);
        }
        local_58 = local_56;
        local_5e = 0;
        while (sVar3 = (*_thunk_FUN_000207d8)(), sVar3 == 0) {
          (*_thunk_FUN_00022eee)();
          sVar3 = (*_thunk_FUN_0002044c)();
          if (sVar3 != 0) goto LAB_00016444;
          sVar3 = (*_thunk_FUN_00020454)();
          if (sVar3 != 0) {
            if (DAT_00027692 == 1) {
              FUN_00018228();
              local_68 = 0xffff;
              goto LAB_00016444;
            }
            if (DAT_00027692 == 5) {
              FUN_00018228();
              local_68 = 1;
              goto LAB_00016444;
            }
          }
        }
        uVar1 = (*_thunk_FUN_000207e4)();
        uVar5 = (ushort)uVar1 & 0xff;
        sVar3 = (*_thunk_FUN_00020700)((ushort)uVar1);
        if ((uVar5 == 0x44) || (uVar5 == 0x43)) goto LAB_00016444;
        if (uVar5 != 0x4f) break;
        local_56 = local_56 + -1;
        if ((local_56 < 0) || ((uVar1 & 0x30000) != 0)) {
          local_56 = 0;
        }
      }
      if (uVar5 != 0x4e) break;
      local_56 = local_56 + 1;
      sVar3 = (*_thunk_FUN_00021e12)(uVar6);
      if ((sVar3 < local_56) || ((uVar1 & 0x30000) != 0)) {
        local_56 = (*_thunk_FUN_00021e12)(uVar6);
      }
    }
    if (uVar5 == 0x4c) break;
    if (uVar5 == 0x4d) {
      local_68 = 1;
LAB_00016444:
      FUN_00016032(param_3._0_2_);
      return local_68;
    }
    if (uVar5 == 0x46) {
LAB_00016340:
      if (param_1[local_56] != '\0') {
        local_5a = local_56;
        do {
          param_1[local_5a] = param_1[(short)(local_5a + 1)];
          local_5a = local_5a + 1;
          local_5e = 1;
        } while (param_1[local_5a] != '\0');
      }
    }
    else if (uVar5 == 0x41) {
      if (local_56 != 0) {
        local_56 = local_56 + -1;
        goto LAB_00016340;
      }
    }
    else {
      sVar4 = (*_thunk_FUN_00020700)(uVar5);
      if ((sVar4 == 0x78) && ((uVar1 & 0x800000) != 0)) {
        local_56 = 0;
        *param_1 = 0;
        local_5e = 1;
      }
      else if ((sVar3 != 0) && (local_56 < param_2._0_2_)) {
        for (local_5a = param_2._0_2_; local_56 < local_5a; local_5a = local_5a + -1) {
          param_1[local_5a] = param_1[(short)(local_5a + -1)];
        }
        param_1[param_2._0_2_] = 0;
        uStack_5b = (undefined1)sVar3;
        param_1[local_56] = uStack_5b;
        local_56 = local_56 + 1;
        if (param_2._0_2_ < local_56) {
          local_56 = param_2._0_2_;
        }
        local_5e = 1;
      }
    }
  }
  local_68 = 0xffff;
  goto LAB_00016444;
}


// ==== load_dash_shapes @ 0001653c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void load_dash_shapes(void)

{
  undefined4 uVar1;
  int extraout_A0;
  
  DAT_00027bb8 = (&PTR_s_shapes_dash_shp_00025858)[night_flag];
  uVar1 = (*_load_shape_bank)(night_flag * 4);
  DAT_0002458a = extraout_A0;
  if (extraout_A0 == 0) {
                    /* WARNING: Could not recover jumptable at 0x00016568. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*_thunk_FUN_0001020e)();
    return;
  }
  dash_frames = uVar1;
  DAT_00027694 = FUN_00015d3e((&PTR_s_shapes_iff_dash_00025848)[night_flag]);
  return;
}


// ==== FUN_00016592 @ 00016592 ====

void FUN_00016592(char *param_1)

{
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    if ((*param_1 == ':') || (*param_1 == '/')) {
      *param_1 = ' ';
    }
  }
  return;
}


// ==== FUN_000165c4 @ 000165c4 ====

void FUN_000165c4(void)

{
  return;
}


// ==== FUN_000165cc @ 000165cc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000165cc(undefined4 param_1)

{
  (*_thunk_FUN_0002085e)(param_1);
  return;
}


// ==== FUN_0001660e @ 0001660e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001660e(void)

{
  DAT_00027bc2 = 0;
  _DAT_00dff080 = *(undefined4 *)(DAT_00026e72 + 0x26);
  (*_thunk_FUN_00022eee)();
  FUN_000124dc(&blank_copper_list);
  FUN_000124dc(&DAT_00027964);
  FUN_000124dc(&screen_memory);
  FUN_000124dc(&DAT_0002794a);
  FUN_000124dc(&DAT_00027958);
  FUN_000124dc(&DAT_00027bb4);
  FUN_000124dc(&ticker_bitmap);
  return;
}


// ==== init_display_memory @ 00016670 ====

void init_display_memory(void)

{
  blank_copper_list = FUN_000165cc(0x90);
  DAT_00027964 = FUN_000165cc(0x10);
  copper_list_init(blank_copper_list,0x90);
  copper_move(blank_copper_list,0x1000200);
  copper_move(blank_copper_list,0x1800000);
  copper_park_sprites(blank_copper_list);
  screen_memory = FUN_000165cc(0x159a0);
  if (screen_memory == 0) {
    FUN_00016e72();
  }
  DAT_00027bac = screen_memory + 0xacd0;
  DAT_0002794a = FUN_000165cc(1000);
  if (DAT_0002794a == 0) {
    FUN_00016e72();
  }
  DAT_00027958 = FUN_000165cc(1000);
  if (DAT_00027958 == 0) {
    FUN_00016e72();
  }
  DAT_00027bb4 = FUN_000165cc(1000);
  if (DAT_00027bb4 == 0) {
    FUN_00016e72();
  }
  ticker_bitmap = FUN_000165cc(0x444);
  if (ticker_bitmap == 0) {
    FUN_00016e72();
  }
  copper_list_init(DAT_0002794a,1000);
  copper_list_init(DAT_00027958,1000);
  copper_list_init(DAT_00027bb4,1000);
  DAT_00027730 = &DAT_00027968;
  DAT_000277dc = &DAT_000279a8;
  DAT_00027888 = &DAT_000279e8;
  DAT_00027934 = &DAT_00027a28;
  DAT_0002727e = &DAT_00027a68;
  DAT_00027734 = &DAT_00027aa8;
  DAT_000277e0 = &DAT_00027ae8;
  view_a = 0;
  view_b = 0x14;
  DAT_0002794e = &DAT_00027698;
  DAT_0002795c = &DAT_00027744;
  DAT_00027952 = screen_memory;
  DAT_00027960 = DAT_00027bac;
  load_copper_list_and_wait(blank_copper_list);
  DAT_00027bbe = blank_copper_list + 4;
  DAT_00027bc2 = *(undefined4 *)(DAT_00026e72 + 0x26);
  DAT_00027bc6 = blank_copper_list + 4;
  return;
}


// ==== init_viewport_bitmap @ 000167f2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void init_viewport_bitmap(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  short local_a;
  short local_8;
  
  *(undefined2 *)(param_1 + 0xa6) = 0;
  *(undefined2 *)(param_1 + 0xa4) = 0;
  *(short *)(param_1 + 0xa8) = param_3._0_2_;
  *(short *)(param_1 + 0xaa) = param_3._2_2_;
  *(undefined2 *)(param_1 + 0x94) = 0;
  *(short *)(param_1 + 0xa2) = param_3._2_2_;
  *(ushort *)(param_1 + 0xa0) = (param_3._0_2_ + 0xfU & 0xfff0) >> 3;
  sVar1 = *(short *)(param_1 + 0xa0);
  for (local_8 = 0; local_8 < param_4._0_2_; local_8 = local_8 + 1) {
    *(int *)(param_1 + local_8 * 4 + 0xc) = *param_2;
    *param_2 = (int)(short)(sVar1 * param_3._2_2_) + *param_2;
  }
  (*_thunk_FUN_00022e5a)(param_1 + 4,(int)param_4._0_2_,(int)param_3._0_2_,(int)param_3._2_2_);
  (*_thunk_FUN_00022e6c)(param_1 + 0x2c);
  *(int *)(param_1 + 0x30) = param_1 + 4;
  if (*(int *)(param_1 + 0x98) != 0) {
    local_a = 0;
    do {
      *(undefined2 *)(*(int *)(param_1 + 0x98) + local_a * 2) = 0;
      local_a = local_a + 1;
    } while (local_a < 0x20);
  }
  if (*(int *)(param_1 + 0x9c) != 0) {
    local_a = 0;
    do {
      *(undefined2 *)(*(int *)(param_1 + 0x9c) + local_a * 2) = 0;
      local_a = local_a + 1;
    } while (local_a < 0x20);
  }
  return;
}


// ==== layout_view_bitmaps @ 0001692c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void layout_view_bitmaps(int param_1)

{
  undefined4 local_c;
  undefined4 *local_8;
  
  local_c = *(undefined4 *)(param_1 + 10);
  (*_thunk_FUN_00022e2e)((short)local_c,0xacd0,1);
  for (local_8 = *(undefined4 **)(param_1 + 6); local_8 != (undefined4 *)0x0;
      local_8 = (undefined4 *)*local_8) {
    init_viewport_bitmap((short)local_8,(short)&local_c);
  }
  build_view_copper_list(param_1);
  return;
}


// ==== setup_menu_screen @ 000169a4 ====

void setup_menu_screen(void)

{
  load_copper_list_and_wait(blank_copper_list);
  *back_playfield_viewport = 0;
  *(undefined2 *)(back_playfield_viewport + 0x2a) = 0x140;
  *(undefined2 *)((int)back_playfield_viewport + 0xaa) = 200;
  *(undefined1 *)((int)back_playfield_viewport + 9) = 4;
  layout_view_bitmaps(back_view);
  return;
}


// ==== FUN_00016a16 @ 00016a16 ====

void FUN_00016a16(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 6);
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 0x2a) = 0x280;
  *(undefined2 *)((int)puVar1 + 0xaa) = 200;
  *(undefined1 *)((int)puVar1 + 9) = 1;
  layout_view_bitmaps(param_1);
  *(undefined2 *)((int)puVar1 + 0xa6) = 5;
  return;
}


// ==== FUN_00016a60 @ 00016a60 ====

void FUN_00016a60(void)

{
  load_copper_list_and_wait(blank_copper_list);
  FUN_00016a16(&view_a);
  FUN_00016a16(&view_b);
  DAT_0002773a = 0xe6;
  DAT_000277e6 = 0xe6;
  flip_views_and_wait(&view_a);
  return;
}


// ==== FUN_00016a98 @ 00016a98 ====

void FUN_00016a98(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 6);
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 0x2a) = 0x140;
  *(undefined2 *)((int)puVar1 + 0xaa) = 200;
  *(undefined1 *)((int)puVar1 + 9) = 5;
  layout_view_bitmaps(param_1);
  return;
}


// ==== FUN_00016ad8 @ 00016ad8 ====

void FUN_00016ad8(void)

{
  load_copper_list_and_wait(blank_copper_list);
  FUN_00016a98(&view_a);
  FUN_00016a98(&view_b);
  flip_views_and_wait(&view_a);
  return;
}


// ==== FUN_00016b04 @ 00016b04 ====

void FUN_00016b04(void)

{
  load_copper_list_and_wait(blank_copper_list);
  DAT_00027698 = 0;
  DAT_00027740 = 0x280;
  DAT_00027742 = 0x93;
  DAT_000276a1 = 3;
  layout_view_bitmaps(&view_a);
  DAT_00027744 = 0;
  DAT_000277ec = 0x280;
  DAT_000277ee = 0x93;
  DAT_0002774d = 3;
  layout_view_bitmaps(&view_b);
  flip_views_and_wait(&view_a);
  return;
}


// ==== FUN_00016b60 @ 00016b60 ====

void FUN_00016b60(void)

{
  load_copper_list_and_wait(blank_copper_list);
  DAT_00027698 = 0;
  DAT_00027740 = 0x280;
  DAT_00027742 = 200;
  DAT_000276a1 = 2;
  layout_view_bitmaps(&view_a);
  DAT_00027744 = 0;
  DAT_000277ec = 0x280;
  DAT_000277ee = 200;
  DAT_0002774d = 2;
  layout_view_bitmaps(&view_b);
  flip_views_and_wait(&view_a);
  return;
}


// ==== clear_ticker @ 00016bbc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void clear_ticker(void)

{
  (*_thunk_FUN_00022e2e)(ticker_bitmap,0x444,1);
  return;
}


// ==== init_ticker_viewport @ 00016bd8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void init_ticker_viewport(void)

{
  ticker_viewport = 0;
  DAT_0002728e = 0x2a0;
  DAT_00027290 = 0xd;
  DAT_00027286 = 0x50;
  DAT_00027288 = 0xd;
  DAT_0002728c = 0xc9;
  DAT_000271ef = 1;
  ticker_bitmap_ptr = ticker_bitmap;
  (*_thunk_FUN_00022e5a)(&DAT_000271ea,1,0x2a0,0xd);
  (*_thunk_FUN_00022e6c)(&DAT_00027212);
  DAT_00027216 = &DAT_000271ea;
  return;
}


// ==== layout_game_viewports @ 00016c38 ====

void layout_game_viewports(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 6);
  puVar1 = (undefined4 *)*puVar2;
  *(undefined2 *)(puVar2 + 0x2a) = 0x140;
  *(undefined2 *)((int)puVar2 + 0xaa) = 0xa2;
  *(undefined1 *)((int)puVar2 + 9) = 5;
  *(undefined2 *)((int)puVar2 + 0x92) = 0x96;
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 0x2a) = 0x280;
  *(undefined2 *)((int)puVar1 + 0xaa) = 0x25;
  *(undefined1 *)((int)puVar1 + 9) = 4;
  layout_view_bitmaps(param_1);
  *puVar1 = &ticker_viewport;
  *(undefined2 *)((int)puVar1 + 0xa6) = 0xa3;
  *(undefined2 *)(puVar2 + 0x25) = 1;
  return;
}


// ==== init_game_display @ 00016cc6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void init_game_display(void)

{
  (*_thunk_FUN_00022e2e)(ticker_bitmap,0x444,1);
  init_ticker_viewport();
  DAT_00027698 = &DAT_000277f0;
  DAT_00027744 = &DAT_0002789c;
  DAT_000277f0 = &ticker_viewport;
  DAT_0002789c = &ticker_viewport;
  ticker_viewport = 0;
  layout_game_viewports(&view_a);
  layout_game_viewports(&view_b);
  build_view_copper_list(&view_a);
  build_view_copper_list(&view_b);
  return;
}


// ==== rebuild_game_display @ 00016d32 ====

void rebuild_game_display(void)

{
  DAT_00027698 = &DAT_000277f0;
  DAT_00027744 = &DAT_0002789c;
  layout_game_viewports(back_view);
  copy_view(front_view,back_view);
  build_view_copper_list(back_view);
  copper_add_ticker_gradient(*(undefined4 *)(back_view + 2));
  return;
}


// ==== FUN_00016d7a @ 00016d7a ====

void FUN_00016d7a(void)

{
  load_copper_list_and_wait(blank_copper_list);
  DAT_00027698 = &DAT_000277f0;
  DAT_00027740 = 0x140;
  DAT_00027742 = 0x4b;
  DAT_000276a1 = 5;
  DAT_000277f0 = 0;
  DAT_00027898 = 0x280;
  DAT_0002789a = 0x91;
  DAT_000277f9 = 4;
  layout_view_bitmaps(&view_a);
  DAT_00027896 = 0x4c;
  build_view_copper_list(&view_a);
  return;
}


// ==== cmap_file_to_palette @ 00016dd6 ====

void cmap_file_to_palette(int *param_1,int param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int *piVar4;
  int *piVar5;
  short local_e;
  byte *local_c;
  
  piVar4 = param_1;
  piVar5 = param_1;
  if (param_1 != (int *)0x0) {
    do {
      param_1 = piVar5;
      if (*param_1 == 0x434d4150) break;
      piVar5 = param_1 + 1;
    } while (param_1 + 1 < piVar4 + 1000);
    local_c = (byte *)(param_1 + 2);
    local_e = 0;
    do {
      pbVar2 = local_c + 1;
      bVar1 = *local_c;
      pbVar3 = local_c + 2;
      local_c = local_c + 3;
      *(ushort *)(param_2 + local_e * 2) =
           (ushort)(*pbVar3 >> 4) | (ushort)*pbVar2 | (ushort)bVar1 << 4;
      local_e = local_e + 1;
    } while (local_e < 0x20);
  }
  return;
}


// ==== FUN_00016e72 @ 00016e72 ====

void FUN_00016e72(void)

{
  FUN_00016e96(s_Not_enough_memory__00016e82);
  return;
}


// ==== FUN_00016e96 @ 00016e96 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016e96(int param_1)

{
  if (param_1 != 0) {
    (*_thunk_FUN_00021ef4)(param_1);
  }
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_00016eb2 @ 00016eb2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016eb2(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00015d3e(param_1);
  if (iVar1 != 0) {
    load_iff_into_viewport(iVar1,param_3);
    (*_thunk_FUN_0002090a)(iVar1);
    build_view_copper_list(param_2);
  }
  return;
}


// ==== FUN_00016eee @ 00016eee ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016eee(undefined4 param_1)

{
  short sVar1;
  short local_6;
  
  (*_thunk_FUN_00022eee)();
  for (local_6 = 1; local_6 < param_1._0_2_; local_6 = local_6 + 1) {
    sVar1 = (*_thunk_FUN_0002044c)();
    if (sVar1 != 0) break;
    (*_thunk_FUN_00022eee)();
  }
  (*_thunk_FUN_0002044c)();
  return;
}


// ==== flip_views @ 00016f20 ====

void flip_views(undefined2 *param_1)

{
  load_copper_list(*(undefined4 *)(param_1 + 1));
  front_view = param_1;
  if (param_1 == &view_a) {
    back_view = &view_b;
  }
  else {
    back_view = &view_a;
  }
  DAT_00026d78 = *(int *)(param_1 + 3);
  DAT_00026d74 = DAT_00026d78 + 0x2c;
  DAT_00026d88 = DAT_00026d78 + 4;
  back_playfield_viewport = *(int *)(back_view + 3);
  back_playfield_rastport = back_playfield_viewport + 0x2c;
  DAT_00026d84 = back_playfield_viewport + 4;
  DAT_00027bbe = *(int *)(param_1 + 1) + 4;
  DAT_00027bc2 = *(undefined4 *)(DAT_00026e72 + 0x26);
  DAT_00027bc6 = *(int *)(back_view + 1) + 4;
  return;
}


// ==== flip_views_and_wait @ 00016fc4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void flip_views_and_wait(undefined4 param_1)

{
  flip_views(param_1);
  (*_wait_vbl_flag)();
  return;
}


// ==== FUN_00016ff6 @ 00016ff6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_00016ff6(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  
  if (param_1._0_2_ != 0xf) {
    uVar1 = (*_thunk_FUN_000223cc)();
    param_2._0_2_ =
         (uVar1 & 0xf00) +
         ((short)(((param_2._0_2_ & 0xf0) - (param_1._2_2_ & 0xf0)) * param_1._0_2_) / 0xf & 0xf0U)
         + ((short)(((param_2._0_2_ & 0xf) - (param_1._2_2_ & 0xf)) * param_1._0_2_) / 0xf & 0xfU) +
           param_1._2_2_;
  }
  return param_2._0_2_;
}


// ==== FUN_00017084 @ 00017084 ====

void FUN_00017084(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined2 auStackY_1008a [32];
  undefined2 auStackY_1004a [32732];
  undefined2 auStack_8a [32];
  undefined2 auStack_4a [32];
  short local_a;
  short local_8;
  short local_6;
  
  local_8 = 1 << (*(byte *)(DAT_00026d78 + 9) & 0x3f);
  for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
    auStack_4a[local_6] = *(undefined2 *)(*(int *)(DAT_00026d78 + 0x98) + local_6 * 2);
  }
  if (*(int *)(DAT_00026d78 + 0x9c) != 0) {
    for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
      auStack_8a[local_6] = *(undefined2 *)(*(int *)(DAT_00026d78 + 0x9c) + local_6 * 2);
    }
  }
  local_a = 0;
  do {
    for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(*(int *)(DAT_00026d78 + 0x98) + local_6 * 2) = uVar2;
      if (*(int *)(DAT_00026d78 + 0x9c) != 0) {
        uVar2 = FUN_00016ff6();
        *(undefined2 *)(*(int *)(DAT_00026d78 + 0x9c) + local_6 * 2) = uVar2;
      }
    }
    uVar1 = *(undefined4 *)(front_view + 2);
    *(undefined4 *)(front_view + 2) = DAT_00027bb4;
    DAT_00027bb4 = uVar1;
    build_view_copper_list(front_view);
    flip_views(front_view);
    local_a = local_a + 1;
  } while (local_a < 0x10);
  return;
}


// ==== FUN_000171f2 @ 000171f2 ====

void FUN_000171f2(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined2 auStackY_100ca [32];
  undefined2 auStackY_1008a [32];
  undefined2 auStackY_1004a [32700];
  undefined2 auStack_ca [32];
  undefined2 auStack_8a [32];
  undefined2 auStack_4a [32];
  short local_a;
  short local_8;
  short local_6;
  
  local_8 = 1 << (*(byte *)((int)DAT_00026d78 + 9) & 0x3f);
  for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
    auStack_4a[local_6] = *(undefined2 *)(DAT_00026d78[0x26] + local_6 * 2);
    auStack_8a[local_6] = *(undefined2 *)(*(int *)(*DAT_00026d78 + 0x98) + local_6 * 2);
    if (DAT_00026d78[0x27] != 0) {
      auStack_ca[local_6] = *(undefined2 *)(DAT_00026d78[0x27] + local_6 * 2);
    }
  }
  local_a = 0;
  do {
    for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(DAT_00026d78[0x26] + local_6 * 2) = uVar2;
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(*(int *)(*DAT_00026d78 + 0x98) + local_6 * 2) = uVar2;
      if (DAT_00026d78[0x27] != 0) {
        uVar2 = FUN_00016ff6();
        *(undefined2 *)(DAT_00026d78[0x27] + local_6 * 2) = uVar2;
      }
    }
    uVar1 = *(undefined4 *)(front_view + 2);
    *(undefined4 *)(front_view + 2) = DAT_00027bb4;
    DAT_00027bb4 = uVar1;
    build_view_copper_list(front_view);
    flip_views(front_view);
    local_a = local_a + 1;
  } while (local_a < 0x10);
  return;
}


// ==== FUN_000173b0 @ 000173b0 ====

void FUN_000173b0(void)

{
  undefined2 auStack_46 [32];
  short local_6;
  
  local_6 = 0;
  do {
    auStack_46[local_6] = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  FUN_00017084(auStack_46);
  return;
}


// ==== FUN_000173e6 @ 000173e6 ====

void FUN_000173e6(void)

{
  undefined2 auStack_46 [32];
  short local_6;
  
  local_6 = 0;
  do {
    auStack_46[local_6] = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  FUN_000171f2(auStack_46,auStack_46);
  return;
}


// ==== FUN_00017422 @ 00017422 ====

void FUN_00017422(undefined4 param_1,int param_2)

{
  undefined2 local_6;
  
  FUN_00016eb2(param_1,back_view,back_playfield_viewport);
  local_6 = 0;
  do {
    if (param_2 != 0) {
      *(undefined2 *)(param_2 + local_6 * 2) =
           *(undefined2 *)(*(int *)(back_playfield_viewport + 0x98) + local_6 * 2);
    }
    *(undefined2 *)(*(int *)(back_playfield_viewport + 0x98) + local_6 * 2) = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  build_view_copper_list(back_view);
  return;
}


// ==== FUN_00017d4e @ 00017d4e ====

void FUN_00017d4e(undefined4 param_1)

{
  undefined4 uVar1;
  short local_6;
  
  uVar1 = *(undefined4 *)(front_view + 2);
  *(undefined4 *)(front_view + 2) = DAT_00027bb4;
  DAT_00027bb4 = uVar1;
  build_view_copper_list(&view_a);
  for (local_6 = 0; local_6 < param_1._0_2_; local_6 = local_6 + 1) {
    copper_wait((short)DAT_0002794a,local_6 + 5);
    copper_move((short)DAT_0002794a,CONCAT22(0x182,local_6 * 0x111));
    if (local_6 == param_1._2_2_) {
      copper_move_long((short)DAT_0002794a);
    }
  }
  if ((param_1._0_2_ <= param_1._2_2_) && (param_1._2_2_ <= (short)(0xc4 - param_1._0_2_))) {
    copper_wait((short)DAT_0002794a,param_1._2_2_ + 5);
    copper_move_long((short)DAT_0002794a);
  }
  while (local_6 = param_1._0_2_ + -1, -1 < local_6) {
    copper_wait((short)DAT_0002794a,0xc9 - local_6);
    copper_move((short)DAT_0002794a,CONCAT22(0x182,local_6 * 0x111));
    param_1._0_2_ = local_6;
    if ((short)(0xc4 - local_6) == param_1._2_2_) {
      copper_move_long((short)DAT_0002794a);
    }
  }
  return;
}


// ==== FUN_00017e80 @ 00017e80 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00017e80(void)

{
  short sVar1;
  short unaff_D4w;
  short sVar2;
  short local_14;
  short local_c;
  short local_a;
  undefined *local_8;
  
  FUN_00016a60();
  (*_thunk_FUN_00021246)((short)DAT_00026d74);
  sVar2 = 0xd2;
  local_8 = PTR_s_A_Time_of_Fury_000258dc;
  local_a = 0;
  local_c = 0;
  do {
    if (local_c % 0xe == 0) {
      sVar1 = 0xc4;
      if (local_c != 0) {
        sVar1 = -0xe;
      }
      (*_thunk_FUN_00022ea4)((short)DAT_00026d74,0);
      (*_thunk_FUN_00022e92)(DAT_00026d74,0,(int)sVar1,0x27f,sVar1 + 0xb);
      (*_thunk_FUN_00022ea4)((short)DAT_00026d74,1);
      if (local_a < 0x35) {
        (*_thunk_FUN_00022e78)(DAT_00026d74,0,sVar1);
        sVar1 = (*_thunk_FUN_00021e12)((short)local_8);
        if (local_8[(short)(sVar1 + 1)] == '\0') {
          FUN_00015a8c(local_8,sVar1,0);
        }
        else {
          FUN_00015a8c(local_8,sVar1,0x267);
        }
        sVar1 = (*_thunk_FUN_00021e12)((short)local_8);
        local_8 = local_8 + (short)(sVar1 + 1);
        unaff_D4w = 0xd2;
      }
      local_a = local_a + 1;
    }
    FUN_00016eee();
    FUN_00017d4e(sVar2);
    flip_views(0x7948);
    FUN_00016eee();
    unaff_D4w = unaff_D4w + -1;
    local_c = local_c + 1;
    *(int *)(DAT_00026d88 + 8) = *(int *)(DAT_00026d88 + 8) + 0x50;
    sVar2 = sVar2 + -1;
    if (sVar2 < 1) {
      sVar2 = 0xd2;
      *(undefined4 *)(DAT_00026d88 + 8) = screen_memory;
      local_c = 0;
    }
    if (unaff_D4w < 0) break;
    sVar1 = (*_thunk_FUN_0002044c)();
  } while (sVar1 == 0);
  local_14 = 0x10;
  do {
    FUN_00017d4e(sVar2);
    flip_views(0x7948);
    FUN_00016eee();
    local_14 = local_14 + -1;
  } while (0 < local_14);
  return;
}


// ==== FUN_00018022 @ 00018022 ====

void FUN_00018022(void)

{
  short sVar1;
  undefined1 auStack_44 [64];
  
  music_play_song(0x8122,2);
  FUN_00017e80();
  music_play_song(0x812b,1);
  FUN_00016ad8();
  FUN_00017422(0x8134,(short)auStack_44);
  flip_views_and_wait((short)back_view);
  FUN_00017084(0x589c);
  sVar1 = FUN_00016eee();
  if (sVar1 == 0) {
    FUN_00017084((short)auStack_44);
    FUN_00017422(0x8146,(short)auStack_44);
    sVar1 = FUN_00016eee();
    if (sVar1 == 0) {
      FUN_000173b0();
      flip_views_and_wait((short)back_view);
      FUN_00017084((short)auStack_44);
      FUN_00017422(0x8158,(short)auStack_44);
      sVar1 = FUN_00016eee();
      if (sVar1 == 0) {
        FUN_000173b0();
        flip_views_and_wait((short)back_view);
        FUN_00017084((short)auStack_44);
        FUN_00016eee();
      }
    }
  }
  FUN_000173b0();
  return;
}


// ==== FUN_0001816c @ 0001816c ====

void FUN_0001816c(void)

{
  FUN_00016e96(s_User_requested_abort__0001817e);
  return;
}


// ==== FUN_00018194 @ 00018194 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00018194(undefined4 param_1)

{
  short sVar1;
  short local_a;
  
  local_a = 0;
  while( true ) {
    sVar1 = (*_thunk_FUN_000207d8)();
    if (sVar1 != 0) {
      sVar1 = (*_thunk_FUN_000207e4)();
      if (sVar1 == 0x4c) {
        return 0xffffffff;
      }
      if (sVar1 == 0x4d) {
        return 1;
      }
      if ((sVar1 == 0x44) || (sVar1 == 0x43)) {
        return 0;
      }
    }
    sVar1 = (*_thunk_FUN_00020454)();
    if (sVar1 == 1) {
      return 0xffffffff;
    }
    if (sVar1 == 5) break;
    sVar1 = (*_thunk_FUN_0002044c)();
    if (sVar1 != 0) {
      return 0;
    }
    (*_thunk_FUN_00022eee)();
    local_a = local_a + 1;
    if ((param_1._0_2_ != 0) && (0x708 < local_a)) {
      return 1000;
    }
  }
  return 1;
}


// ==== FUN_00018228 @ 00018228 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00018228(void)

{
  short sVar1;
  undefined2 local_6;
  
  local_6 = 0;
  do {
    (*_thunk_FUN_00022eee)();
    sVar1 = (*_thunk_FUN_000207d8)();
    if (sVar1 == 0) {
      sVar1 = (*_thunk_FUN_0002044c)();
      if (sVar1 == 0) {
        sVar1 = (*_thunk_FUN_00020454)();
        if (sVar1 == 0) goto LAB_0001824c;
      }
    }
    else {
LAB_0001824c:
      local_6 = 1000;
    }
    local_6 = local_6 + 1;
    if (8 < local_6) {
      return;
    }
  } while( true );
}


// ==== rank_select_screen @ 00018262 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * rank_select_screen(void)

{
  int iVar1;
  short sVar2;
  int local_50;
  short local_4a;
  undefined1 auStack_48 [64];
  undefined4 local_8;
  
  DAT_00026bb4._0_2_ = 0;
  music_play_song(0x84f0,4);
  FUN_00016ad8();
  DAT_00026c90 = 0;
  FUN_00017422(0x84f9,(short)auStack_48);
  local_8 = FUN_00015d4c(0x850b);
  local_4a = DAT_00026bb4._0_2_;
  (*_thunk_FUN_00021246)((short)back_playfield_rastport);
  (*_set_clip_full_bitmap)();
  local_50 = (*_thunk_FUN_0002050e)((short)local_8);
  (*_thunk_FUN_00020e0a)((short)local_50,*(undefined2 *)(local_50 + 10));
  flip_views_and_wait((short)back_view);
  FUN_00017084((short)auStack_48);
  copy_view((short)front_view,(short)back_view);
LAB_00018302:
  do {
    sVar2 = FUN_00018194();
    if (sVar2 != 0) {
      if (sVar2 != 1000) {
        DAT_00026bb4._0_2_ = sVar2 + DAT_00026bb4._0_2_;
        if (DAT_00026bb4._0_2_ < 0) {
          DAT_00026bb4._0_2_ = 7;
        }
        if (7 < DAT_00026bb4._0_2_) {
          DAT_00026bb4._0_2_ = 0;
        }
        if (DAT_00026bb4._0_2_ != local_4a) {
          (*_thunk_FUN_00021246)((short)back_playfield_rastport);
          (*_thunk_FUN_00020e0a)((short)local_50,*(undefined2 *)(local_50 + 10));
          local_50 = (*_thunk_FUN_0002050e)((short)local_8);
          (*_thunk_FUN_00020e0a)((short)local_50,*(undefined2 *)(local_50 + 10));
          flip_views_and_wait((short)back_view);
          copy_view((short)front_view,(short)back_view);
          local_4a = DAT_00026bb4._0_2_;
          FUN_00018228();
        }
        goto LAB_00018302;
      }
      demo_mode = 1;
    }
    if (DAT_00026bb4._0_2_ != 7) {
      (*_thunk_FUN_0002090a)((short)local_8);
      FUN_000173b0();
      if ((demo_mode == 0) && (DAT_00026ed6 != 0)) {
        demo_buffer = (*_thunk_FUN_00020848)(5000);
        demo_mode = 2;
      }
      if (demo_mode == 1) {
        demo_buffer = FUN_00015d3e(0x8521);
      }
      demo_pos = 0;
      if (demo_buffer == 0) {
        demo_mode = 0;
      }
      if (demo_mode != 0) {
        (*_thunk_FUN_00015d5a)();
        (*_thunk_FUN_000203da)();
      }
      DAT_000254a8 = DAT_00026bb4._0_2_;
      rank = DAT_00026bb4._0_2_;
      if (demo_mode == 1) {
        rank = (short)*(char *)(demo_buffer + demo_pos);
        demo_pos = demo_pos + 1;
      }
      if (demo_mode == 2) {
        iVar1 = (int)demo_pos;
        demo_pos = demo_pos + 1;
        *(undefined1 *)(demo_buffer + iVar1) = (undefined1)rank;
      }
      mission_in_rank = 1;
      goto LAB_000184d6;
    }
    sVar2 = load_save_game_dialog();
    if (sVar2 == 0) {
      DAT_00026c90 = 1;
      (*_thunk_FUN_0002090a)((short)local_8);
      FUN_000173b0();
LAB_000184d6:
      music_stop_unload();
      return (&rank_start_map_names)[DAT_000254a8];
    }
    FUN_00016a98((short)back_view);
    copy_view((short)front_view,(short)back_view);
    build_view_copper_list((short)back_view);
  } while( true );
}


// ==== finish_demo_recording @ 0001852a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void finish_demo_recording(void)

{
  if ((demo_mode == 2) && (DAT_00026ed6 != 0)) {
    *(undefined1 *)(demo_buffer + demo_pos) = 0xff;
    (*_thunk_FUN_0001fe50)(DAT_00026ed6,demo_buffer,5000);
  }
  FUN_000124dc(&demo_buffer);
  demo_mode = 0;
  return;
}


// ==== FUN_00018570 @ 00018570 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00018570(undefined4 param_1)

{
  short sVar1;
  
  sVar1 = (*_thunk_FUN_00021e12)(param_1);
  FUN_00015910(param_1,(int)sVar1);
  return;
}


// ==== mission_briefing_screen @ 00018590 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 mission_briefing_screen(void)

{
  int iVar1;
  uint uVar2;
  char cVar4;
  short sVar3;
  undefined2 uVar5;
  short local_84;
  undefined1 auStack_76 [50];
  undefined1 auStack_44 [64];
  
  FUN_00016b04();
  iVar1 = (*_thunk_FUN_000204f4)((short)DAT_00024582,0x6e6b);
  uVar5 = (undefined2)back_playfield_rastport;
  (*_thunk_FUN_00021246)(uVar5);
  (*_set_clip_full_bitmap)();
  (*_thunk_FUN_00021eca)(0x587c,(short)auStack_44);
  (*_thunk_FUN_00020cc4)((short)iVar1,0,0x65 - (*(ushort *)(iVar1 + 2) >> 1));
  (*_thunk_FUN_00022e78)(uVar5,0x128,0x3d);
  FUN_00018570((short)(&rank_name_table)[rank]);
  (*_thunk_FUN_00022e78)(uVar5,0x154,0x49);
  (*_thunk_FUN_000215d8)((short)auStack_76,0x8764);
  FUN_00018570((short)auStack_76);
  (*_thunk_FUN_00022e78)(uVar5,0x154,0x77);
  (*_thunk_FUN_000215d8)((short)auStack_76,0x8767);
  FUN_00018570((short)auStack_76);
  (*_thunk_FUN_00022e78)(uVar5,0x154,0x83);
  (*_thunk_FUN_000215d8)((short)auStack_76,0x876a);
  FUN_00018570((short)auStack_76);
  flip_views_and_wait((short)back_view);
  FUN_00017084((short)auStack_44);
  (*_thunk_FUN_00022eee)();
  local_84 = 1;
  do {
    if ((0xef < local_84) || (sVar3 = (*_thunk_FUN_0002044c)(), sVar3 != 0)) {
      FUN_000173b0();
      return 0;
    }
    (*_thunk_FUN_00022eee)();
    sVar3 = (*_thunk_FUN_000207d8)();
    if (sVar3 != 0) {
      uVar2 = (*_thunk_FUN_000207e4)();
      if (((uVar2 & 0x80000) != 0) && (cVar4 = (*_thunk_FUN_00020700)((short)uVar2), cVar4 == 'r'))
      {
        FUN_000173b0();
        return 1;
      }
    }
    local_84 = local_84 + 1;
  } while( true );
}


// ==== update_waterline_split @ 0001876e ====

void update_waterline_split(void)

{
  undefined2 uVar1;
  
  uVar1 = *(undefined2 *)(*(int *)(back_view + 2) + 2);
  *(undefined2 *)(*(int *)(back_view + 2) + 2) = split_wait_index;
  copper_wait(*(undefined4 *)(back_view + 2));
  *(undefined2 *)(*(int *)(back_view + 2) + 2) = uVar1;
  return;
}


// ==== copper_add_ticker_gradient @ 000187ba ====

void copper_add_ticker_gradient(undefined4 param_1)

{
  short local_6;
  
  local_6 = 0;
  do {
    copper_wait(param_1,local_6 + 0xc9);
    copper_move(param_1,*(undefined2 *)(&DAT_000258e4 + local_6 * 2));
    local_6 = local_6 + 1;
  } while (local_6 < 10);
  return;
}


// ==== setup_level_display @ 00018806 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void setup_level_display(void)

{
  short local_6;
  
  load_copper_list_and_wait(blank_copper_list);
  init_game_display();
  load_iff_into_viewport(DAT_00027694,*back_playfield_viewport);
  (*_thunk_FUN_0002090a)(DAT_00027694);
  local_6 = 0;
  do {
    *(undefined2 *)(&DAT_000279e8 + local_6 * 2) =
         *(undefined2 *)(*(int *)(*back_playfield_viewport + 0x98) + local_6 * 2);
    *(undefined2 *)(&DAT_00027a28 + local_6 * 2) =
         *(undefined2 *)(*(int *)(*back_playfield_viewport + 0x98) + local_6 * 2);
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  ticker_message = 0;
  ticker_scroll_count = 0;
  FUN_00015d3e((&PTR_s_shapes_wingspalette_00025840)[night_flag]);
  cmap_file_to_palette(DAT_00027bca,back_playfield_viewport[0x26]);
  (*_thunk_FUN_0002090a)(DAT_00027bca);
  FUN_00015d3e((&PTR_s_shapes_ocean_palette_00025850)[night_flag]);
  cmap_file_to_palette(DAT_00027bca,back_playfield_viewport[0x27]);
  (*_thunk_FUN_0002090a)(DAT_00027bca);
  *(undefined2 *)(*(int *)(*(int *)*back_playfield_viewport + 0x98) + 2) = 0x777;
  load_copper_list_and_wait(blank_copper_list);
  copy_view(back_view,front_view);
  build_view_copper_list(back_view);
  build_view_copper_list(front_view);
  copper_add_ticker_gradient(*(undefined4 *)(back_view + 2));
  copper_add_ticker_gradient(*(undefined4 *)(front_view + 2));
  build_enemy_plane_frame_tables();
  return;
}


// ==== FUN_00018958 @ 00018958 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00018958(void)

{
  short sVar1;
  short local_6;
  
  local_6 = 0;
  do {
    (*_thunk_FUN_00022ec4)(DAT_00026d74,0);
    sVar1 = (*_thunk_FUN_00021e12)(&DAT_00027bce + local_6 * 0x1d);
    (*_thunk_FUN_00022e78)
              (DAT_00026d74,0x2d,(ushort)(*(short *)(DAT_00026d74 + 0x3e) + local_6 * 0x10) + 0x3d);
    (*_thunk_FUN_00022ed4)(DAT_00026d74,&DAT_00027bce + local_6 * 0x1d,(int)sVar1);
    if (sVar1 < 0x1c) {
      (*_thunk_FUN_00022ed4)(DAT_00026d74,PTR_s__000258e0,(int)(short)(0x1c - sVar1));
    }
    local_6 = local_6 + 1;
  } while (local_6 < 6);
  return;
}


// ==== FUN_00018a06 @ 00018a06 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00018a06(void)

{
  undefined2 extraout_D0u;
  undefined2 extraout_D0u_00;
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  short sVar4;
  int local_c;
  short local_6;
  
  local_c = 0;
  local_6 = 0;
  do {
    (&DAT_00027bce)[local_6 * 0x1d] = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 6);
  FUN_00018958(0);
  iVar2 = (*_thunk_FUN_00020848)(0x104);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    local_c = (*_thunk_FUN_00022b1e)(0,0xfffe);
    if (local_c == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = (*_thunk_FUN_00022ade)((short)local_c,(short)iVar2);
      if ((short)uVar3 != 0) {
        local_6 = 0;
        while ((local_6 < 6 &&
               (sVar4 = (*_thunk_FUN_00022aec)((short)local_c,(short)iVar2), sVar4 != 0))) {
          sVar4 = (*_thunk_FUN_00021e82)();
          if (((sVar4 == 0x77) &&
              (((sVar4 = (*_thunk_FUN_00021e82)(), sVar4 == 0x6f &&
                (sVar4 = (*_thunk_FUN_00021e82)(), sVar4 == 0x66)) &&
               (*(char *)(iVar2 + 0xb) == '.')))) && (*(char *)(iVar2 + 0xc) != '\0')) {
            (*_thunk_FUN_000222d2)(local_6 * 0x1d + 0x7bce,(short)iVar2 + 0xc);
            (*_thunk_FUN_00021e02)(local_6 * 0x1d + 0x7c7c,local_6 * 0x1d + 0x7bce);
            local_6 = local_6 + 1;
          }
        }
        uVar3 = FUN_00018958();
      }
    }
  }
  uVar1 = (undefined2)((uint)uVar3 >> 0x10);
  if (local_c != 0) {
    (*_thunk_FUN_00022b54)((short)local_c);
    uVar1 = extraout_D0u;
  }
  if (iVar2 != 0) {
    (*_thunk_FUN_0002090a)((short)iVar2);
    uVar1 = extraout_D0u_00;
  }
  return CONCAT22(uVar1,local_6);
}


// ==== load_save_game_dialog @ 00018b96 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 load_save_game_dialog(undefined4 param_1)

{
  undefined2 uVar1;
  short sVar2;
  short local_10c;
  undefined1 local_108 [50];
  undefined2 local_d6;
  undefined4 local_d4;
  undefined4 local_d0;
  short *local_ca;
  undefined **local_c6;
  short local_c2;
  short asStack_c0 [29];
  short asStack_86 [29];
  short local_4c;
  short local_4a;
  short local_48;
  short local_46;
  undefined1 auStack_44 [64];
  
  setup_menu_screen();
  local_c6 = &PTR_DAT_000258f8;
  local_ca = &DAT_00025918;
  local_d0 = back_playfield_rastport;
  local_d4 = back_view;
  (*_thunk_FUN_00021246)((short)back_playfield_rastport);
  (*_set_clip_full_bitmap)();
  (*_thunk_FUN_00022ea4)((short)local_d0,0x28f);
  (*_thunk_FUN_00022ec4)((short)local_d0,0);
  for (; *local_c6 != (undefined *)0x0; local_c6 = local_c6 + 2) {
    (*_thunk_FUN_00022e78)
              ((short)local_d0,*(undefined2 *)(local_c6 + 1),*(undefined2 *)((int)local_c6 + 6));
    uVar1 = (*_thunk_FUN_00021e12)((short)*local_c6);
    (*_thunk_FUN_00022ed4)((short)local_d0,(short)*local_c6,uVar1);
  }
  (*_thunk_FUN_00022e78)((short)local_d0,0x55,0x13);
  if (param_1._0_2_ == 0) {
    (*_thunk_FUN_00022ed4)((short)local_d0,0x9254,4);
  }
  else {
    (*_thunk_FUN_00022ed4)((short)local_d0,0x9259,4);
  }
  for (; (*local_ca != 0 && (local_ca[3] != 0)); local_ca = local_ca + 4) {
    (*_thunk_FUN_00022e78)((short)local_d0,*local_ca,local_ca[1]);
    (*_thunk_FUN_00022e48)((short)local_d0,local_ca[2],local_ca[1]);
    (*_thunk_FUN_00022e48)((short)local_d0,local_ca[2],local_ca[3]);
    (*_thunk_FUN_00022e48)((short)local_d0,*local_ca,local_ca[3]);
    (*_thunk_FUN_00022e48)((short)local_d0,*local_ca,local_ca[1]);
  }
  (*_thunk_FUN_00021eca)(0x5960,(short)auStack_44);
  flip_views_and_wait((short)local_d4);
  FUN_00017084((short)auStack_44);
  local_4c = 0;
  do {
    (&DAT_00027bce)[local_4c * 0x1d] = 0;
    local_4c = local_4c + 1;
  } while (local_4c < 6);
  local_48 = 0;
  do {
    asStack_86[local_48] = 0x2c;
    asStack_c0[local_48] = local_48 * 0x10 + 0x3d;
    local_48 = local_48 + 1;
  } while (local_48 < 6);
  local_48 = 0;
  local_46 = 0;
  (*_thunk_FUN_00021246)((short)DAT_00026d74);
  (*_set_clip_full_bitmap)();
  FUN_000134a4();
  local_c2 = FUN_00018a06();
  if ((local_c2 == 0) && (param_1._0_2_ == 0)) {
    local_48 = 7;
  }
  do {
    uVar1 = (undefined2)DAT_00026d74;
    if (local_48 < 6) {
      if (param_1._0_2_ == 0) {
        (*_thunk_FUN_00022ec4)(uVar1,2);
        (*_thunk_FUN_00022e92)
                  (DAT_00026d74,asStack_86[local_48],asStack_c0[local_48] + -1,
                   asStack_86[local_48] + 0xed,asStack_c0[local_48] + 7);
        (*_thunk_FUN_00022ec4)((short)DAT_00026d74,1);
        local_4a = FUN_00018194();
        FUN_00018228();
      }
      else {
        (*_thunk_FUN_00022ec4)(uVar1,0);
        (*_thunk_FUN_00022ea4)((short)DAT_00026d74,0x28f);
        local_4a = (*_text_input_field)(local_48 * 0x1d + 0x7bce,asStack_86[local_48],1);
      }
    }
    else {
      (*_thunk_FUN_00022ec4)(uVar1,2);
      if (local_48 == 6) {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0x2d,0xb9,0x91,0xc5);
      }
      else if (local_48 == 7) {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0xcf,0xb9,0x11b,0xc5);
      }
      (*_thunk_FUN_00022ec4)((short)DAT_00026d74,1);
      local_4a = FUN_00018194();
      FUN_00018228();
    }
    sVar2 = local_48;
    local_46 = local_48;
    do {
      local_48 = local_4a + local_48;
      if (local_48 < 0) {
        local_48 = 7;
      }
      if (7 < local_48) {
        local_48 = 0;
      }
    } while (((param_1._0_2_ == 0) && (local_48 < 6)) && ((&DAT_00027bce)[local_48 * 0x1d] == '\0'))
    ;
    if (local_48 != sVar2) {
      (*_thunk_FUN_00022ec4)((short)DAT_00026d74,2);
      if (local_46 < 6) {
        if (param_1._0_2_ == 0) {
          (*_thunk_FUN_00022e92)
                    (DAT_00026d74,asStack_86[local_46],asStack_c0[local_46] + -1,
                     asStack_86[local_46] + 0xed,asStack_c0[local_46] + 7);
        }
      }
      else if (local_46 == 6) {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0x2d,0xb9,0x91,0xc5);
      }
      else {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0xcf,0xb9,0x11b,0xc5);
      }
      (*_thunk_FUN_00022ec4)((short)DAT_00026d74,1);
    }
  } while (local_4a != 0);
  FUN_00016592(local_48 * 0x1d + 0x7bce);
  if ((local_48 < 6) && ((&DAT_00027bce)[local_48 * 0x1d] != '\0')) {
    (*_thunk_FUN_00022ea4)((short)DAT_00026d74,1);
    local_108[0] = 0;
    (*_thunk_FUN_000222a8)((short)local_108,0x925e);
    (*_thunk_FUN_000222a8)((short)local_108,local_48 * 0x1d + 0x7bce);
    (*_thunk_FUN_00022e78)((short)DAT_00026d74,10,10);
    if (param_1._0_2_ == 0) {
      (*_thunk_FUN_00022ed4)((short)DAT_00026d74,0x9263,0xf);
      music_stop_unload();
      FUN_00012bbe();
      FUN_00015e1a((short)local_108);
    }
    else {
      (*_thunk_FUN_00022ed4)((short)DAT_00026d74,0x9273,0xe);
      FUN_00015e8a((short)local_108);
      for (local_10c = 0; local_10c < local_c2; local_10c = local_10c + 1) {
        if (((&DAT_00027c7c)[local_10c * 0x1d] != '\0') &&
           (sVar2 = (*_thunk_FUN_00021e9a)(local_10c * 0x1d + 0x7bce,local_10c * 0x1d + 0x7c7c),
           sVar2 != 0)) {
          local_108[0] = 0;
          (*_thunk_FUN_000222a8)((short)local_108,0x9282);
          (*_thunk_FUN_000222a8)((short)local_108,local_10c * 0x1d + 0x7c7c);
          (*_thunk_FUN_00022ace)((short)local_108);
          break;
        }
      }
      FUN_000173b0();
      flip_views_and_wait((short)back_view);
    }
    local_d6 = 0;
  }
  else {
    FUN_000173b0();
    if (local_48 == 6) {
      FUN_00016e96(0);
    }
    flip_views_and_wait((short)back_view);
    local_d6 = 0xffff;
  }
  load_engine_sound();
  return local_d6;
}


// ==== save_high_scores @ 00019288 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void save_high_scores(void)

{
  (*_thunk_FUN_0001fe50)(s_highscore_000192a4,high_score_table_ptr,0x168);
  return;
}


// ==== sort_high_scores @ 00019320 ====

void sort_high_scores(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 auStack_2c [9];
  short local_8;
  short local_6;
  
  do {
    local_6 = 0;
    local_8 = 0;
    do {
      if (*(int *)(high_score_table_ptr + local_8 * 0x24) <
          *(int *)(high_score_table_ptr + (short)(local_8 + 1) * 0x24)) {
        sVar1 = 8;
        puVar2 = auStack_2c;
        puVar3 = (undefined4 *)(high_score_table_ptr + local_8 * 0x24);
        do {
          *puVar2 = *puVar3;
          sVar1 = sVar1 + -1;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        } while (sVar1 != -1);
        sVar1 = 8;
        puVar2 = (undefined4 *)(high_score_table_ptr + local_8 * 0x24);
        puVar3 = (undefined4 *)(high_score_table_ptr + (short)(local_8 + 1) * 0x24);
        do {
          *puVar2 = *puVar3;
          sVar1 = sVar1 + -1;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        } while (sVar1 != -1);
        sVar1 = 8;
        puVar2 = (undefined4 *)(high_score_table_ptr + (short)(local_8 + 1) * 0x24);
        puVar3 = auStack_2c;
        do {
          *puVar2 = *puVar3;
          sVar1 = sVar1 + -1;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        } while (sVar1 != -1);
        local_6 = 1;
      }
      local_8 = local_8 + 1;
    } while (local_8 < 9);
  } while (local_6 != 0);
  return;
}


// ==== load_high_scores @ 000193cc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void load_high_scores(void)

{
  int iVar1;
  undefined2 local_6;
  
  iVar1 = (*_thunk_FUN_00022b30)(0x945a,0x3ed);
  if (iVar1 == 0) {
    local_6 = 0;
    do {
      *(undefined4 *)(high_score_table_ptr + local_6 * 0x24) = 0;
      *(undefined2 *)(high_score_table_ptr + local_6 * 0x24 + 4) = 0;
      (*_thunk_FUN_000222d2)((short)high_score_table_ptr + local_6 * 0x24 + 6,0x9464);
      local_6 = local_6 + 1;
    } while (local_6 < 10);
  }
  else {
    (*_thunk_FUN_00022b42)((short)iVar1,(short)high_score_table_ptr,0x168);
    (*_thunk_FUN_00022ab2)((short)iVar1);
  }
  return;
}


// ==== high_score_check_and_entry @ 00019472 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void high_score_check_and_entry(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  ushort local_58;
  undefined1 auStack_55 [17];
  undefined1 auStack_44 [64];
  
  for (local_58 = 0; local_58 < 0x11; local_58 = local_58 + 1) {
    auStack_55[(short)local_58] = 0;
  }
  load_high_scores();
  sort_high_scores();
  if (*(int *)(high_score_table_ptr + 0x144) < score) {
    setup_menu_screen();
    uVar2 = (undefined2)back_playfield_rastport;
    (*_thunk_FUN_00021246)(uVar2);
    (*_set_clip_full_bitmap)();
    (*_thunk_FUN_00022ea4)(uVar2,8);
    (*_thunk_FUN_00022ec4)(uVar2,0);
    uVar4 = 0x964e;
    uVar3 = 0x9669;
    (*_thunk_FUN_00022e78)
              (uVar2,0x34,0x53,s_in_the_hall_of_fame__00019669,s_Your_name_is_to_be_entered_0001964e
              );
    uVar1 = (*_thunk_FUN_00021e12)(uVar4);
    (*_thunk_FUN_00022ed4)(uVar2,uVar4,uVar1);
    (*_thunk_FUN_00022e78)(uVar2,0x5b,0x5c);
    uVar1 = (*_thunk_FUN_00021e12)(uVar3);
    (*_thunk_FUN_00022ed4)(uVar2,uVar3,uVar1);
    (*_thunk_FUN_00022ea4)(uVar2,2);
    (*_thunk_FUN_00022e78)(uVar2,0x50,100);
    (*_thunk_FUN_00022e48)(uVar2,0xe1,100);
    (*_thunk_FUN_00022e48)(uVar2,0xe1,0x71);
    (*_thunk_FUN_00022e48)(uVar2,0x50,0x71);
    (*_thunk_FUN_00022e48)(uVar2,0x50,100);
    (*_thunk_FUN_00021eca)(0x59ac,(short)auStack_44);
    flip_views_and_wait((short)back_view);
    FUN_00017084((short)auStack_44);
    (*_text_input_field)((short)auStack_55,0x52,10000);
    *(int *)(high_score_table_ptr + 0x144) = score;
    (*_thunk_FUN_000222d2)((short)(high_score_table_ptr + 0x14a),(short)auStack_55);
    *(undefined2 *)(high_score_table_ptr + 0x148) = rank;
    FUN_000173b0();
    sort_high_scores();
    save_high_scores();
  }
  return;
}


// ==== draw_high_score_table @ 0001967e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_high_score_table(void)

{
  undefined1 auStack_74 [100];
  undefined4 local_10;
  short local_c;
  short local_a;
  short local_8;
  short local_6;
  
  local_10 = back_playfield_rastport;
  (*_thunk_FUN_00021246)((short)back_playfield_rastport);
  local_6 = 0;
  do {
    local_8 = 0;
    do {
      if (*(int *)(high_score_table_ptr + local_8 * 0x24) != 0) {
        local_a = *(short *)(&DAT_000259a6 + local_6 * 2) + 0xd;
        local_c = local_8 * 0xc + *(short *)(&DAT_000259a6 + local_6 * 2) + 6;
        (*_thunk_FUN_00022ea4)((short)local_10,*(undefined2 *)(&DAT_000259a0 + local_6 * 2));
        (*_thunk_FUN_00022ec4)((short)local_10,0);
        (*_thunk_FUN_00022e78)((short)local_10,local_a,local_c);
        (*_thunk_FUN_000215d8)((short)auStack_74,0x9846);
        FUN_00018570((short)auStack_74);
        (*_thunk_FUN_00022e78)((short)local_10,local_a + 0x28,local_c);
        (*_thunk_FUN_000215d8)
                  ((short)auStack_74,0x9849,
                   (short)*(undefined4 *)(high_score_table_ptr + local_8 * 0x24));
        FUN_00018570((short)auStack_74);
        (*_thunk_FUN_00022e78)((short)local_10,local_a + 0x96,local_c);
        (*_thunk_FUN_000215d8)
                  ((short)auStack_74,0x984f,
                   (short)(&rank_name_table)[*(short *)(high_score_table_ptr + local_8 * 0x24 + 4)])
        ;
        FUN_00018570((short)auStack_74);
        (*_thunk_FUN_00022e78)((short)local_10,local_a + 300,local_c);
        FUN_00018570((short)high_score_table_ptr + local_8 * 0x24 + 6);
      }
      local_8 = local_8 + 1;
    } while (local_8 < 10);
    local_6 = local_6 + 1;
  } while (local_6 < 3);
  return;
}


// ==== high_score_screen @ 00019856 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void high_score_screen(void)

{
  undefined1 auStack_21e [410];
  undefined1 auStack_84 [64];
  undefined1 auStack_44 [64];
  
  high_score_table_ptr = auStack_21e;
  music_play_song(0x9928,0);
  high_score_check_and_entry();
  FUN_00016d7a();
  back_view = &view_a;
  back_playfield_viewport = *DAT_0002794e;
  back_playfield_rastport = back_playfield_viewport + 0x2c;
  DAT_00026d84 = back_playfield_viewport + 4;
  FUN_00017422(0x9931,(short)auStack_84);
  (*_thunk_FUN_00021246)((short)back_playfield_rastport);
  (*_set_clip_full_bitmap)();
  draw_high_score_table();
  back_playfield_viewport = *(int *)(back_view + 3);
  back_playfield_rastport = back_playfield_viewport + 0x2c;
  DAT_00026d84 = back_playfield_viewport + 4;
  FUN_00017422(0x9944,(short)auStack_44);
  flip_views_and_wait((short)back_view);
  FUN_000171f2((short)auStack_44,(short)auStack_84);
  FUN_00016eee();
  FUN_000173e6();
  return;
}


// ==== copper_list_reset @ 00019958 ====

void copper_list_reset(int param_1)

{
  *(undefined2 *)(param_1 + 2) = 0;
  return;
}


// ==== copper_list_init @ 00019968 ====

void copper_list_init(short *param_1,int param_2)

{
  *param_1 = (short)(param_2 - 4U >> 2) + -1;
  copper_list_reset(param_1);
  return;
}


// ==== copper_move @ 000199bc ====

void copper_move(short *param_1,undefined4 param_2)

{
  short sVar1;
  
  if (param_1[1] < *param_1) {
    param_1[param_1[1] * 2 + 2] = param_2._0_2_;
    sVar1 = param_1[1];
    param_1[1] = param_1[1] + 1;
    param_1[sVar1 * 2 + 3] = param_2._2_2_;
  }
  return;
}


// ==== copper_move_long @ 00019a08 ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== copper_wait @ 00019a9c ====

void copper_wait(short *param_1,undefined4 param_2)

{
  short sVar1;
  
  param_2._0_2_ = (short)param_2._0_2_ / 4 << 1;
  param_2._2_2_ = param_2._2_2_ + 0x2c;
  if ((short)param_2._0_2_ < 0) {
    param_2._0_2_ = 0;
  }
  if (0xe2 < (short)param_2._0_2_) {
    param_2._0_2_ = 0xe2;
  }
  if (param_2._2_2_ < 0) {
    param_2._2_2_ = 0;
  }
  if (0x106 < param_2._2_2_) {
    param_2._2_2_ = 0x106;
  }
  if (0xff < param_2._2_2_) {
    copper_wait(param_1,0xd3);
  }
  if (param_1[1] < *param_1) {
    param_1[param_1[1] * 2 + 2] = (param_2._0_2_ & 0xfe) + param_2._2_2_ * 0x100 + 1;
    sVar1 = param_1[1];
    param_1[1] = param_1[1] + 1;
    param_1[sVar1 * 2 + 3] = -2;
  }
  return;
}


// ==== copper_add_colors @ 00019b5a ====

void copper_add_colors(short *param_1,short *param_2,undefined4 param_3,undefined4 param_4)

{
  short *psVar1;
  ushort local_6;
  
  if ((param_3._0_2_ != 0) || (param_3._2_2_ != 0)) {
    copper_wait(param_1,param_3._2_2_);
  }
  if ((short)(*param_1 - param_1[1]) < (short)param_4._0_2_) {
    param_4._0_2_ = *param_1 - param_1[1];
  }
  if (0 < (short)param_4._0_2_) {
    psVar1 = param_1 + param_1[1] * 2;
    for (local_6 = 0; local_6 < param_4._0_2_; local_6 = local_6 + 1) {
      psVar1[2] = local_6 * 2 + 0x180;
      psVar1[3] = *param_2;
      param_2 = param_2 + 1;
      psVar1 = psVar1 + 2;
    }
    param_1[1] = param_4._0_2_ + param_1[1];
  }
  return;
}


// ==== copper_add_viewport_palette @ 00019c0a ====

void copper_add_viewport_palette(undefined4 param_1,int param_2)

{
  copper_add_colors(param_1,*(undefined4 *)(param_2 + 0x98),*(short *)(param_2 + 0xa6) + -1);
  return;
}


// ==== copper_add_split_palette @ 00019c80 ====

void copper_add_split_palette(undefined4 param_1,int param_2)

{
  undefined2 local_6;
  
  copper_wait(param_1,*(undefined2 *)(param_2 + 0x92));
  for (local_6 = 0; local_6 < (ushort)(1 << (*(byte *)(param_2 + 9) & 0x3f)); local_6 = local_6 + 1)
  {
    if (*(short *)(*(int *)(param_2 + 0x9c) + (short)local_6 * 2) !=
        *(short *)(*(int *)(param_2 + 0x98) + (short)local_6 * 2)) {
      copper_move(param_1,*(undefined2 *)(*(int *)(param_2 + 0x9c) + (short)local_6 * 2));
    }
  }
  return;
}


// ==== copper_add_viewport_display @ 00019d18 ====

void copper_add_viewport_display(undefined2 param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short local_1c;
  short sVar6;
  short local_18;
  ushort local_e;
  ushort local_c;
  ushort local_8;
  
  copper_wait(param_1,CONCAT22(param_3._0_2_,param_3._2_2_ + -1));
  copper_move(param_1,0x1000200);
  bVar1 = 0x3c < *(ushort *)(param_2 + 0xa0);
  if (bVar1) {
    param_3._0_2_ = (short)param_3._0_2_ >> 1;
  }
  local_18 = 0;
  sVar6 = 0;
  sVar5 = 0;
  local_1c = 0;
  if (param_3._2_2_ < -0x2a) {
    local_1c = -0x2a - param_3._2_2_;
  }
  if (0x118 < (ushort)(param_3._2_2_ + *(short *)(param_2 + 0xa2))) {
    sVar5 = 0x118 - (param_3._2_2_ + *(short *)(param_2 + 0xa2));
  }
  if (((-0x150 < (short)param_3._0_2_) && ((short)param_3._0_2_ < 0x13f)) &&
     ((ushort)(sVar5 + local_1c) < *(ushort *)(param_2 + 0xa2))) {
    sVar4 = (short)(param_3._0_2_ & 0xfff0) / 8;
    copper_move(param_1,CONCAT22(0x102,(param_3._0_2_ & 0xf) * 0x11),sVar5,0);
    if (2 < sVar4) {
      sVar6 = sVar4 + -2;
    }
    if ((short)param_3._0_2_ < -0x3f) {
      local_18 = -6 - sVar4;
    }
    sVar4 = param_3._0_2_ + local_18 * 8;
    sVar2 = local_1c + param_3._2_2_ + 0x2c;
    sVar3 = sVar6 * -8;
    sVar5 = (sVar2 + *(short *)(param_2 + 0xa2)) - (sVar5 + local_1c);
    if (bVar1) {
      local_18 = local_18 * 2;
      sVar6 = sVar6 * 2;
      local_c = (short)(sVar4 + 0x78) >> 1 & 0xfc;
      local_e = local_c + (*(short *)(param_2 + 0xa0) - (local_18 + sVar6 + 4)) * 2;
    }
    else {
      local_c = (short)(sVar4 + 0x70) >> 1 & 0xf8;
      local_e = local_c + (*(short *)(param_2 + 0xa0) - (local_18 + sVar6 + 2)) * 4;
    }
    local_e = local_e & 0xff;
    copper_move(param_1,CONCAT22(0x8e,(sVar4 + 0x81U & 0xff) + sVar2 * 0x100));
    copper_move(param_1,CONCAT22(0x90,param_3._0_2_ + 0xc1 + sVar3 + sVar5 * 0x100));
    copper_move(param_1,CONCAT22(0x92,local_c));
    copper_move(param_1,CONCAT22(0x94,local_e));
    copper_move(param_1,CONCAT22(0x108,local_18 +
                                       sVar6 + (*(short *)(param_2 + 4) - *(short *)(param_2 + 0xa0)
                                               )));
    copper_move(param_1,CONCAT22(0x10a,local_18 +
                                       sVar6 + (*(short *)(param_2 + 4) - *(short *)(param_2 + 0xa0)
                                               )));
    for (local_8 = 0; local_8 < *(byte *)(param_2 + 9); local_8 = local_8 + 1) {
      copper_move_long(param_1);
    }
    copper_wait(param_1,CONCAT22(param_3._0_2_,param_3._2_2_));
    copper_move(param_1,CONCAT22(0x100,((ushort)bVar1 * 8 + (ushort)*(byte *)(param_2 + 9)) * 0x1000
                                       + 0x200));
    if (sVar5 < 0x80) {
      copper_wait(param_1,sVar5 + -0x2c);
      copper_move(param_1,0x1000200);
    }
  }
  return;
}


// ==== copper_park_sprites @ 0001a06c ====

void copper_park_sprites(undefined2 param_1)

{
  undefined2 local_6;
  
  local_6 = 0;
  do {
    copper_move(param_1,CONCAT22(local_6 * 4 + 0x140,0x300));
    copper_move(param_1,CONCAT22(local_6 * 4 + 0x142,0x406));
    copper_move_long(param_1);
    local_6 = local_6 + 1;
  } while (local_6 < 8);
  return;
}


// ==== build_view_copper_list @ 0001a0d4 ====

void build_view_copper_list(int param_1)

{
  int *local_8;
  
  copper_list_reset(*(undefined4 *)(param_1 + 2));
  copper_move(*(undefined4 *)(param_1 + 2),0x1000200);
  copper_park_sprites(*(undefined4 *)(param_1 + 2));
  for (local_8 = *(int **)(param_1 + 6); local_8 != (int *)0x0; local_8 = (int *)*local_8) {
    if (*(int **)(param_1 + 6) != local_8) {
      copper_wait(*(undefined4 *)(param_1 + 2),*(short *)((int)local_8 + 0xa6) + -1);
      copper_move(*(undefined4 *)(param_1 + 2),0x1000200);
    }
    if ((*local_8 == 0) ||
       (*(short *)((int)local_8 + 0xa6) < (short)(*(short *)(*local_8 + 0xa6) + -1))) {
      copper_add_viewport_palette(*(undefined4 *)(param_1 + 2),local_8);
      copper_add_viewport_display(*(undefined4 *)(param_1 + 2),local_8,local_8[0x29]);
      if ((*(short *)(local_8 + 0x25) != 0) && (local_8[0x27] != 0)) {
        split_wait_index = *(undefined2 *)(*(int *)(param_1 + 2) + 2);
        copper_add_split_palette(*(undefined4 *)(param_1 + 2),local_8);
      }
    }
  }
  return;
}


// ==== iff_cmap_to_palette @ 0001a1f6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void iff_cmap_to_palette(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar4 = (byte *)(param_1 + 8);
  sVar2 = (*_thunk_FUN_000223cc)();
  if (0x20 < sVar2) {
    sVar2 = 0x20;
  }
  for (sVar3 = 0; sVar3 < sVar2; sVar3 = sVar3 + 1) {
    pbVar5 = pbVar4 + 1;
    bVar1 = *pbVar4;
    pbVar6 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *(ushort *)(*(int *)(param_2 + 0x98) + sVar3 * 2) =
         *pbVar5 & 0xf0 | (short)(ushort)*pbVar6 >> 4 | (bVar1 & 0xf0) << 4;
  }
  return;
}


// ==== iff_cmp2_to_split_palette @ 0001a284 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void iff_cmp2_to_split_palette(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  sVar2 = (*_thunk_FUN_000223cc)();
  if (0x20 < sVar2) {
    sVar2 = 0x20;
  }
  *(undefined2 *)(param_2 + 0x92) = *(undefined2 *)(param_1 + 8);
  *(undefined2 *)(param_2 + 0x90) = 0;
  *(undefined2 *)(param_2 + 0x94) = 1;
  pbVar4 = (byte *)(param_1 + 0xc);
  for (sVar3 = 0; sVar3 < sVar2; sVar3 = sVar3 + 1) {
    pbVar5 = pbVar4 + 1;
    bVar1 = *pbVar4;
    pbVar6 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *(ushort *)(*(int *)(param_2 + 0x9c) + sVar3 * 2) =
         *pbVar5 & 0xf0 | (short)(ushort)*pbVar6 >> 4 | (bVar1 & 0xf0) << 4;
  }
  return;
}


// ==== FUN_0001a336 @ 0001a336 ====

void FUN_0001a336(int param_1,uint *param_2)

{
  *param_2 = *param_2 + *(int *)(param_1 + *param_2 + 4) + 9 & 0xfffffffe;
  return;
}


// ==== iff_decode_body @ 0001a362 ====

void iff_decode_body(short *param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined4 auStackY_20028 [32766];
  undefined4 auStack_28 [6];
  ushort local_10;
  short local_e;
  short local_c;
  ushort local_a;
  short local_8;
  short local_6;
  
  local_a = (ushort)(*param_1 + 7U) >> 3;
  if ((ushort)param_1[1] < *(ushort *)(param_3 + 0xaa)) {
    local_e = param_1[1];
  }
  else {
    local_e = *(short *)(param_3 + 0xaa);
  }
  if (*(byte *)(param_1 + 4) < *(byte *)(param_3 + 9)) {
    bVar1 = *(byte *)(param_1 + 4);
  }
  else {
    bVar1 = *(byte *)(param_3 + 9);
  }
  local_10 = (ushort)bVar1;
  for (local_c = 0; local_c < (short)local_10; local_c = local_c + 1) {
    auStack_28[local_c] = *(undefined4 *)(param_3 + local_c * 4 + 0xc);
  }
  FUN_0001a74c((short)param_3);
  for (local_6 = 0; local_6 < local_e; local_6 = local_6 + 1) {
    for (local_8 = 0; local_8 < (short)local_10; local_8 = local_8 + 1) {
      FUN_000203e8((short)&param_2,(short)auStack_28 + local_8 * 4);
    }
  }
  return;
}


// ==== iff_parse_chunks @ 0001a452 ====

void iff_parse_chunks(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int local_18;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_18 = 0;
  local_c = 0xc;
  iVar1 = *(int *)(param_1 + 4);
  while (local_c < iVar1 + 8) {
    iVar2 = *(int *)(param_1 + local_c);
    if (iVar2 == 0x424d4844) {
      local_8 = local_c + param_1 + 8;
    }
    else if (iVar2 == 0x424f4459) {
      local_18 = local_c + param_1 + 8;
    }
    else if (iVar2 == 0x434d4150) {
      iff_cmap_to_palette(local_c + param_1,param_2);
    }
    else if (iVar2 == 0x434d5032) {
      iff_cmp2_to_split_palette(local_c + param_1,param_2);
    }
    FUN_0001a336(param_1,&local_c);
    if ((39999 < local_c) || (local_c < 1)) break;
  }
  if ((local_8 != 0) && (local_18 != 0)) {
    iff_decode_body(local_8,local_18,param_2);
  }
  return;
}


// ==== load_iff_into_viewport @ 0001a548 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void load_iff_into_viewport(int *param_1,int param_2)

{
  if ((param_1 == (int *)0x0) || (param_2 == 0)) {
    (*_thunk_FUN_00021dce)(s_____Error___null_pointer_passed_t_0001a5b0);
  }
  else if ((*param_1 == 0x464f524d) && (param_1[2] == 0x494c424d)) {
    iff_parse_chunks(param_1,param_2);
  }
  return;
}


// ==== FUN_0001a60e @ 0001a60e ====

void FUN_0001a60e(short *param_1,int param_2,int param_3,undefined4 param_4)

{
  short *psVar1;
  short local_e;
  short local_c;
  short local_a;
  short *local_8;
  
  for (local_a = 0; local_a < param_4._0_2_; local_a = local_a + 1) {
    local_c = 0;
    psVar1 = param_1;
    for (local_e = 0; local_8 = psVar1 + 2, local_e < param_1[1]; local_e = local_e + 1) {
      if ((short)(local_a * 2 + 0x180) == *local_8) {
        if (local_c == 0) {
          psVar1[3] = *(short *)(param_3 + local_a * 2);
        }
        local_c = local_c + 1;
      }
      psVar1 = local_8;
    }
    *(undefined2 *)(*(int *)(param_2 + 0x98) + local_a * 2) = *(undefined2 *)(param_3 + local_a * 2)
    ;
  }
  return;
}


// ==== FUN_0001a6ac @ 0001a6ac ====

void FUN_0001a6ac(short *param_1,int param_2,int param_3,undefined4 param_4)

{
  short *psVar1;
  short local_e;
  short local_c;
  short local_a;
  short *local_8;
  
  for (local_a = 0; local_a < param_4._0_2_; local_a = local_a + 1) {
    local_c = 0;
    psVar1 = param_1;
    for (local_e = 0; local_8 = psVar1 + 2, local_e < param_1[1]; local_e = local_e + 1) {
      if ((short)(local_a * 2 + 0x180) == *local_8) {
        if (local_c == 1) {
          psVar1[3] = *(short *)(param_3 + local_a * 2);
        }
        local_c = local_c + 1;
      }
      psVar1 = local_8;
    }
    *(undefined2 *)(*(int *)(param_2 + 0x9c) + local_a * 2) = *(undefined2 *)(param_3 + local_a * 2)
    ;
  }
  return;
}


// ==== FUN_0001a74c @ 0001a74c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001a74c(int param_1)

{
  ushort local_a;
  
  for (local_a = 0; local_a < *(byte *)(param_1 + 9); local_a = local_a + 1) {
    (*_thunk_FUN_00022e2e)
              (*(undefined4 *)((short *)(param_1 + 4) + (short)local_a * 2 + 4),
               *(short *)(param_1 + 6) * *(short *)(param_1 + 4),1);
  }
  return;
}


// ==== copy_view_bitmaps @ 0001a834 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void copy_view_bitmaps(int param_1,int param_2)

{
  undefined4 *local_c;
  undefined4 *local_8;
  
  if ((param_1 != 0) && (param_2 != 0)) {
    local_8 = *(undefined4 **)(param_1 + 6);
    for (local_c = *(undefined4 **)(param_2 + 6);
        (local_8 != (undefined4 *)0x0 && (local_c != (undefined4 *)0x0));
        local_c = (undefined4 *)*local_c) {
      (*_thunk_FUN_00022e0c)
                (local_8 + 1,0,0,local_c + 1,0,0,(uint)*(ushort *)(local_8 + 1) << 3,
                 *(undefined2 *)((int)local_8 + 6),0xcc,0xffffffff,0);
      local_8 = (undefined4 *)*local_8;
    }
  }
  return;
}


// ==== copy_view_palettes @ 0001a8c4 ====

void copy_view_palettes(int param_1,int param_2)

{
  undefined4 *local_c;
  undefined4 *local_8;
  
  if ((param_1 != 0) && (param_2 != 0)) {
    local_8 = *(undefined4 **)(param_1 + 6);
    for (local_c = *(undefined4 **)(param_2 + 6);
        (local_8 != (undefined4 *)0x0 && (local_c != (undefined4 *)0x0));
        local_c = (undefined4 *)*local_c) {
      *(undefined2 *)(local_c + 0x24) = *(undefined2 *)(local_8 + 0x24);
      *(undefined2 *)((int)local_c + 0x92) = *(undefined2 *)((int)local_8 + 0x92);
      *(undefined2 *)(local_c + 0x25) = *(undefined2 *)(local_8 + 0x25);
      *(undefined2 *)((int)local_c + 0x96) = *(undefined2 *)((int)local_8 + 0x96);
      if ((local_8[0x26] != 0) && (local_c[0x26] != 0)) {
        FUN_0001a60e(*(undefined4 *)(param_2 + 2),local_c,local_8[0x26]);
      }
      if ((local_8[0x27] != 0) && (local_c[0x27] != 0)) {
        FUN_0001a6ac(*(undefined4 *)(param_2 + 2),local_c,local_8[0x27]);
      }
      local_8 = (undefined4 *)*local_8;
    }
  }
  return;
}


// ==== copy_view @ 0001a9ca ====

void copy_view(int param_1,int param_2)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    copy_view_bitmaps(param_1,param_2);
    copy_view_palettes(param_1,param_2);
  }
  return;
}


// ==== load_copper_list_and_wait @ 0001a9fc ====

void load_copper_list_and_wait(undefined4 param_1)

{
  load_copper_list(param_1);
  wait_vbl_flag();
  return;
}


// ==== load_copper_list @ 0001aa0e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void load_copper_list(int param_1)

{
  DAT_00027d2e = param_1;
  *(undefined4 *)(param_1 + 4 + (int)(short)(*(short *)(param_1 + 2) << 2)) = 0xfffffffe;
  _DAT_00dff080 = param_1 + 4;
  vbl_flag = 0;
  return;
}


// ==== wait_next_vbl @ 0001aa32 ====

/* WARNING: Removing unreachable block (ram,0x0001aa3c) */

void wait_next_vbl(void)

{
                    /* WARNING: Do nothing block with infinite loop */
  do {
  } while( true );
}


// ==== wait_vbl_flag @ 0001aa3e ====

void wait_vbl_flag(void)

{
  do {
  } while (vbl_flag == '\0');
  vbl_flag = 0;
  return;
}


// ==== FUN_0001aa50 @ 0001aa50 ====

void FUN_0001aa50(void)

{
  DAT_00027d32 = 1;
  DAT_00027d34 = 0;
  return;
}


// ==== no_enemy_on_tail @ 0001aa6e ====

undefined2 no_enemy_on_tail(void)

{
  short local_8;
  undefined2 local_6;
  
  local_6 = 1;
  if (*(short *)(player_plane_ptr + 0xc) == 0) {
    DAT_00027d40 = &enemy_planes;
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
      if ((((*DAT_00027d40 == 2) && (DAT_00027d40[1] == 1)) && (DAT_00027d40[2] == 3)) &&
         ((0xc < DAT_00027d40[0xb] && (DAT_00027d40[0xb] < 0xe)))) {
        local_6 = 0;
      }
      DAT_00027d40 = DAT_00027d40 + 0x1a;
    }
  }
  return local_6;
}


// ==== wheel_clearance @ 0001aaea ====

short wheel_clearance(void)

{
  short local_6;
  
  local_6 = 0xb;
  if (((turn_frame == 0) || (*(short *)(player_plane_ptr + 0xc) == 1)) ||
     (*(short *)(player_plane_ptr + 0xc) == 0xb)) {
    local_6 = *(short *)(&DAT_000259fc + (uint)attitude_frame_no * 2);
    if (gear_target != 0) {
      local_6 = *(short *)(&DAT_00025a12 + (uint)attitude_frame_no * 2) + local_6;
    }
  }
  else if (turn_frame < 6) {
    local_6 = (&DAT_00025a50)[turn_frame];
  }
  else if (0x13 < turn_frame) {
    local_6 = (&DAT_00025a50)[(short)(0x19 - turn_frame)];
  }
  return local_6;
}


// ==== turn_step @ 0001ab80 ====

void turn_step(int param_1)

{
  short sVar1;
  
  sVar1 = no_enemy_on_tail();
  if ((sVar1 != 0) && (turn_step_timer = turn_step_timer + -1, turn_step_timer == 0)) {
    turn_step_timer = 2;
    sVar1 = turn_frame + 1;
    if (sVar1 < 0x1a) {
      if ((0x13 < sVar1) && (param_1 == 0)) {
        sVar1 = sVar1 + (turn_frame + -0xc) * -2;
      }
      turn_frame = sVar1;
      if (turn_frame == 0xe) {
        *(short *)(player_plane_ptr + 0x14) = -*(short *)(player_plane_ptr + 0x14);
      }
    }
    else {
      turn_frame = 0;
    }
  }
  return;
}


// ==== select_hellcat_frame @ 0001abde ====

undefined4 select_hellcat_frame(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  if (param_1._0_2_ == 0) {
LAB_0001abec:
    if (turn_frame == 0) {
      iVar1 = FUN_0001cb30(DAT_0002458e,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
      iVar2 = FUN_0001cb30(DAT_00024592,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
      if (*(short *)(iVar1 + 8) != (short)(param_1._2_2_ + 1)) {
        *(short *)(iVar1 + 8) = param_1._2_2_ + 1;
        FUN_00015b58(iVar1);
      }
      if (*(short *)(iVar2 + 8) != (short)(param_1._2_2_ + 1)) {
        *(short *)(iVar2 + 8) = param_1._2_2_ + 1;
        FUN_00015b58(iVar2);
      }
      local_8 = *(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4);
      attitude_frame_no = *(undefined2 *)(&DAT_00025a28 + param_2._0_2_ * 2);
    }
    else {
      attitude_frame_no = 0;
      if (*(short *)(player_plane_ptr + 0x14) == -1) {
        local_8 = *(undefined4 *)(&DAT_00025c60 + param_2._0_2_ * 4);
      }
      else {
        local_8 = *(undefined4 *)(&DAT_00025cc8 + param_2._0_2_ * 4);
      }
    }
  }
  else {
    if (param_1._0_2_ != 1) {
      if (param_1._0_2_ == 4) goto LAB_0001abec;
      if (param_1._0_2_ != 0xb) {
        iVar1 = FUN_0001cb30(DAT_0002458e,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
        iVar2 = FUN_0001cb30(DAT_00024592,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
        if (*(short *)(iVar1 + 8) != (short)(param_1._2_2_ + 1)) {
          FUN_00015b58(iVar1);
          *(short *)(iVar1 + 8) = param_1._2_2_ + 1;
        }
        if (*(short *)(iVar2 + 8) != (short)(param_1._2_2_ + 1)) {
          FUN_00015b58(iVar2);
          *(short *)(iVar2 + 8) = param_1._2_2_ + 1;
        }
        attitude_frame_no = *(undefined2 *)(&DAT_00025a28 + param_2._0_2_ * 2);
        return *(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4);
      }
    }
    if (deck_tail_up == 0) {
      local_c = FUN_0001cb30(DAT_0002458e,*(undefined4 *)(&DAT_00025c30 + param_2._0_2_ * 4));
      local_10 = FUN_0001cb30(DAT_00024592,*(undefined4 *)(&DAT_00025c30 + param_2._0_2_ * 4));
      local_8 = *(undefined4 *)(&DAT_00025c30 + param_2._0_2_ * 4);
    }
    else {
      param_2._0_2_ = 9;
      local_c = FUN_0001cb30(DAT_0002458e,DAT_00025d54);
      local_10 = FUN_0001cb30(DAT_00024592,DAT_00025d54);
      local_8 = DAT_00025d54;
    }
    if (*(short *)(local_c + 8) != (short)(param_1._2_2_ + 1)) {
      FUN_00015b58(local_c);
      *(short *)(local_c + 8) = param_1._2_2_ + 1;
    }
    if (*(short *)(local_10 + 8) != (short)(param_1._2_2_ + 1)) {
      FUN_00015b58(local_10);
      *(short *)(local_10 + 8) = param_1._2_2_ + 1;
    }
    DAT_00027d36 = *(undefined2 *)(&DAT_00025c50 + param_2._0_2_ * 2);
    attitude_frame_no = 4;
  }
  return local_8;
}


// ==== wreck_explosions @ 0001aed8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void wreck_explosions(void)

{
  undefined4 uVar1;
  ushort uVar2;
  undefined2 uVar3;
  bool bVar4;
  undefined2 uVar5;
  short local_8;
  
  uVar1 = map_ptr_from_x();
  uVar3 = (undefined2)((uint)player_plane_ptr >> 0x10);
  uVar5 = (undefined2)player_plane_ptr;
  local_8 = wheel_clearance();
  local_8 = *(short *)CONCAT22(uVar3,uVar5) - local_8;
  bVar4 = *(short *)(player_plane_ptr + 0xc) == 6;
  if (bVar4) {
    local_8 = 0;
  }
  engine_volume_target = 0;
  if ((ticks_since_crash < 0x4b) && (next_wreck_explosion <= ticks_since_crash)) {
    uVar2 = FUN_00021e24();
    uVar2 = uVar2 & 0xc;
    next_wreck_explosion = uVar2 + ticks_since_crash;
    FUN_00021e24(bVar4);
    uVar3 = map_ptr_from_x(local_8,uVar2,uVar1);
    (*_spawn_explosion_at_cell)(uVar3);
  }
  return;
}


// ==== respawn_timer @ 0001af7c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void respawn_timer(void)

{
  if ((lives == '\x01') || (lives == '\0')) {
    game_over_display = 1;
  }
  ticks_since_crash = ticks_since_crash + 1;
  if ((ticks_since_crash == 0x96) || ((0x1e < ticks_since_crash && ((input_word & 0x30) != 0)))) {
    (*_lose_life_and_respawn)();
  }
  return;
}


// ==== player_crash_update @ 0001afba ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void player_crash_update(void)

{
  bool bVar1;
  bool bVar2;
  short *psVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  short local_14;
  short local_12;
  short local_6;
  
  local_6 = 1;
  bVar2 = false;
  bVar1 = false;
  local_14 = wheel_clearance();
  sVar4 = map_ptr_from_x();
  sVar5 = map_cell_is_sea(sVar4);
  if (sVar5 == 0) {
    sVar5 = map_cell_is_ship(sVar4);
    if (sVar5 != 0) {
      local_6 = 3;
    }
  }
  else {
    local_6 = 2;
  }
  uVar9 = SUB42(player_plane_ptr,0);
  uVar8 = (undefined2)((uint)player_plane_ptr >> 0x10);
  if (local_6 == 1) {
    sVar5 = wheel_clearance();
    if (((short)(*(short *)CONCAT22(uVar8,uVar9) - sVar5) < 1) && (turn_frame == 0)) {
      attitude_frame_no = 0;
      pitch_smooth = 0;
      pitch_cmd = 0;
      sVar5 = wheel_clearance();
      *player_plane_ptr = sVar5;
      select_hellcat_frame(player_plane_ptr[10]);
      bVar1 = true;
      (*_spawn_explosion_at_cell)(sVar4,0);
    }
    else {
      bVar2 = true;
    }
  }
  else if (local_6 == 2) {
    sVar5 = wheel_clearance();
    bVar1 = *(short *)CONCAT22(uVar8,uVar9) <= sVar5;
    if (bVar1) {
      attitude_frame_no = 0;
      pitch_smooth = 0;
      pitch_cmd = 0;
      sVar5 = wheel_clearance();
      *player_plane_ptr = sVar5;
      (*_thunk_FUN_000152ac)(*player_plane_ptr + 5);
    }
  }
  else if (local_6 == 3) {
    sVar6 = player_airspeed / 100;
    sVar5 = player_plane_ptr[10];
    sVar7 = object_height(sVar4);
    local_14 = sVar7 + local_14;
    if (*player_plane_ptr <= local_14) {
      sVar7 = map_cell_is_sea(sVar4 + player_plane_ptr[10] * -10);
      if (sVar7 == 0) {
        bVar1 = true;
        attitude_frame_no = 0;
        pitch_smooth = 0;
        pitch_cmd = 0;
        uVar8 = (undefined2)((uint)player_plane_ptr >> 0x10);
        uVar9 = SUB42(player_plane_ptr,0);
        sVar5 = wheel_clearance();
        sVar6 = object_height(sVar4);
        *(short *)CONCAT22(uVar8,uVar9) = sVar6 + sVar5;
      }
      else {
        player_plane_ptr[1] = player_plane_ptr[1] - (sVar6 * sVar5 + 4);
        player_airspeed = 0;
        set_screen_flash(0xf00);
        local_14 = 2;
        (*_spawn_explosion_at_cell)(sVar4,0);
      }
    }
  }
  if (turn_frame < 0xe) {
    turn_frame = turn_frame + -2;
    if (turn_frame < 0) {
      turn_frame = 0;
    }
  }
  else {
    if (turn_frame == 0xe) {
      player_plane_ptr[10] = -player_plane_ptr[10];
    }
    turn_frame = turn_frame + 2;
    if (0x19 < turn_frame) {
      turn_frame = 0;
    }
  }
  if ((turn_frame == 0) || (local_14 < *player_plane_ptr)) {
    if (bVar1) {
      player_plane_ptr[1] = (player_airspeed / 100) * player_plane_ptr[10] + player_plane_ptr[1];
      player_airspeed = player_airspeed + -0x55;
      if (player_airspeed < 100) {
        player_airspeed = 0;
      }
      if (local_6 == 2) {
        (*_thunk_FUN_000152ac)(*player_plane_ptr + 5);
      }
      else {
        (*_spawn_explosion_at_cell)(*player_plane_ptr,0);
        if (local_6 == 1) {
          (*_ground_impact_at_cell)(sVar4);
          (*_thunk_FUN_00011a84)(8);
        }
      }
    }
    else {
      pitch_cmd = pitch_cmd - pitch_rate;
      if (pitch_cmd < -0xc1c) {
        pitch_cmd = -0xc1c;
      }
      bVar2 = true;
    }
  }
  else {
    local_12 = 0xb;
    if (turn_frame < 6) {
      local_12 = (&DAT_00025a50)[turn_frame];
    }
    else if (0x13 < turn_frame) {
      local_12 = (&DAT_00025a50)[(short)(0x19 - turn_frame)];
    }
    sVar5 = map_cell_is_ship(sVar4);
    if ((sVar5 != 0) || (sVar5 = map_cell_is_sea(sVar4), sVar5 != 0)) {
      uVar8 = (undefined2)((uint)player_plane_ptr >> 0x10);
      uVar9 = SUB42(player_plane_ptr,0);
      sVar5 = object_height(sVar4);
      *(short *)CONCAT22(uVar8,uVar9) = local_12 + sVar5;
    }
    player_plane_ptr[1] = (player_airspeed / 100) * player_plane_ptr[10] + player_plane_ptr[1];
    game_vbl_timer = 0;
  }
  psVar3 = player_plane_ptr;
  if (bVar2) {
    player_plane_ptr[0xc] = player_plane_ptr[0xc] + -1;
    if (psVar3[0xc] < -10) {
      player_plane_ptr[0xc] = -10;
    }
    *player_plane_ptr = player_plane_ptr[0xc] + *player_plane_ptr;
    uVar8 = (undefined2)((uint)player_plane_ptr >> 0x10);
    uVar9 = SUB42(player_plane_ptr,0);
    sVar5 = wheel_clearance();
    if ((short)(*(short *)CONCAT22(uVar8,uVar9) - sVar5) < 1) {
      sVar5 = wheel_clearance();
      *player_plane_ptr = sVar5;
      (*_spawn_explosion_at_cell)(sVar4,0);
    }
    player_plane_ptr[1] = (player_airspeed / 100) * player_plane_ptr[10] + player_plane_ptr[1];
  }
  if (((player_airspeed == 0) && (turn_frame == 0)) && (*player_plane_ptr <= local_14)) {
    sVar5 = map_cell_is_sea(sVar4);
    if ((sVar5 == 0) &&
       ((sVar4 = map_cell_is_ship(sVar4), sVar4 == 0 || (0x13 < *player_plane_ptr)))) {
      player_plane_ptr[6] = 8;
    }
    else {
      player_plane_ptr[6] = 6;
    }
    player_plane_ptr[9] = 0;
    player_plane_ptr[0xd] = 0;
    next_wreck_explosion = 0;
    ticks_since_crash = 0;
    sink_subcounter = 0;
  }
  return;
}


// ==== update_gear_target @ 0001b45a ====

int update_gear_target(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (int)*(short *)(player_plane_ptr + 0xc);
  if (iVar2 == 0) {
    sVar1 = *(short *)(player_plane_ptr + 0xc) >> 0xf;
    iVar3 = CONCAT22(sVar1,*carrier_home_ptr - DAT_00025e52);
    if (((short)(*carrier_home_ptr - DAT_00025e52) < *(short *)(player_plane_ptr + 2)) &&
       (iVar3 = CONCAT22(sVar1,DAT_00025e52 + *carrier_home_ptr),
       *(short *)(player_plane_ptr + 2) < (short)(DAT_00025e52 + *carrier_home_ptr))) {
      if (carrier_alive == 0) {
        gear_target = 0;
      }
      else {
        gear_target = 5;
      }
    }
    else {
      gear_target = 0;
    }
  }
  else {
    iVar3 = 0;
    if (((iVar2 == 1) || (iVar3 = 0, iVar2 == 7)) || (iVar3 = iVar2 + -0xb, iVar3 == 0)) {
      gear_target = 5;
      gear_anim = 5;
    }
    else {
      gear_target = 0;
    }
  }
  return iVar3;
}


// ==== player_on_elevator @ 0001b4de ====

undefined2 player_on_elevator(void)

{
  undefined2 local_a;
  short local_8;
  short local_6;
  
  local_a = 0;
  if (*(short *)(player_plane_ptr + 0xc) == 1) {
    if (*(short *)(player_plane_ptr + 0x14) < 0) {
      local_6 = *(short *)(player_plane_ptr + 2) - *(short *)(&DAT_00025d80 + turn_frame * 2);
      local_8 = *(short *)(player_plane_ptr + 2) + *(short *)(&DAT_00025d8e + turn_frame * 2);
    }
    else {
      local_6 = *(short *)(player_plane_ptr + 2) - *(short *)(&DAT_00025d8e + turn_frame * 2);
      local_8 = *(short *)(player_plane_ptr + 2) + *(short *)(&DAT_00025d80 + turn_frame * 2);
    }
    if (local_6 < (short)(*carrier_home_ptr + -0x17)) {
      deck_crew_signal = 1;
    }
    else if ((short)(*carrier_home_ptr + 0x21) < local_8) {
      deck_crew_signal = 0;
    }
    else {
      local_a = 1;
    }
  }
  return local_a;
}


// ==== player_fire_input @ 0001b5b0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort player_fire_input(void)

{
  short *psVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  
  uVar2 = input_word & 0x30;
  if ((input_word & 0x30) == 0) {
    gun_firing = 0;
  }
  else if (player_plane_ptr[6] == 0) {
    if ((input_word & 0x20) == 0) {
      if ((turn_frame == 0) && (0 < gun_ammo)) {
        gun_firing = 1;
      }
      else {
        gun_firing = 0;
      }
    }
    else if ((turn_frame < 6) || (0x10 < turn_frame)) {
      uVar2 = (*_fire_ordnance)();
    }
  }
  else if ((((player_plane_ptr[6] == 1) && (*(short *)(carrier_home_ptr + 2) == 0)) &&
           (carrier_hp != 0)) &&
          ((uVar2 = player_on_elevator(), uVar2 != 0 && (player_airspeed == 0)))) {
    deck_crew_signal = 3;
    *(undefined2 *)(carrier_home_ptr + 2) = 3;
    player_plane_ptr[6] = 0xb;
    psVar1 = player_plane_ptr;
    engine_volume_target = 0;
    sVar3 = wheel_clearance();
    uVar4 = map_ptr_from_x();
    uVar2 = object_height(uVar4);
    *psVar1 = uVar2 + sVar3;
  }
  return uVar2;
}


// ==== player_gun_vs_enemy_planes @ 0001b682 ====

void player_gun_vs_enemy_planes(void)

{
  short sVar1;
  undefined2 *puVar2;
  short local_10;
  short local_e;
  
  if (gun_firing != 0) {
    DAT_00027d40 = &enemy_planes;
    for (local_e = 0; local_e < 4; local_e = local_e + 1) {
      if (DAT_00027d40[2] == 3) {
        local_10 = player_plane_ptr[1] - DAT_00027d40[0x10];
        if (local_10 < 0) {
          local_10 = -local_10;
        }
        sVar1 = *player_plane_ptr - DAT_00027d40[0x13];
        if (sVar1 < 0) {
          sVar1 = -sVar1;
        }
        if (((local_10 < 0xa0) && (sVar1 < 0x14)) && (pitch_cmd == 0)) {
          DAT_00027d40[3] = 1;
          puVar2 = DAT_00027d40;
          DAT_00027d40[5] = DAT_00027d40[5] + -1;
          if ((short)puVar2[5] < 1) {
            FUN_0001cae0(6,CONCAT22(DAT_00027d40[0x10] + -0x10,DAT_00027d40[0x13] + 10));
            DAT_00027d40[4] = DAT_00027d40[4] + -8;
            if ((short)DAT_00027d40[4] < 0x60) {
              score = score + 0x15e;
              *DAT_00027d40 = 4;
              DAT_00027d40[0x12] = 0xfffd;
              DAT_00027d40[0xb] = 0;
              *(byte *)((int)DAT_00027d40 + 3) = *(byte *)((int)DAT_00027d40 + 3) & 0xf7;
              enemy_plane_set_sprite(DAT_00027d40);
            }
            puVar2 = DAT_00027d40;
            sVar1 = rand_mod();
            puVar2[5] = sVar1 + 6;
          }
        }
      }
      DAT_00027d40 = DAT_00027d40 + 0x1a;
    }
  }
  return;
}


// ==== init_carrier_deck_bounds @ 0001b7bc ====

void init_carrier_deck_bounds(void)

{
  carrier_home_ptr = &carrier_home_x;
  own_carrier_x_start = ship_own_carrier * 4 + 0x10;
  own_carrier_x_end = DAT_0002542a * 4 + -0x10;
  return;
}


// ==== player_reset @ 0001b7ec ====

void player_reset(void)

{
  short sVar2;
  undefined4 uVar1;
  undefined2 *puVar3;
  
  player_plane_ptr = &player_y;
  init_carrier_deck_bounds();
  *player_plane_ptr = 0;
  player_plane_ptr[0xb] = 0;
  player_plane_ptr[0xc] = 0;
  player_plane_ptr[6] = 1;
  puVar3 = player_plane_ptr;
  sVar2 = rand_mod();
  puVar3[8] = sVar2 + 6;
  player_plane_ptr[9] = 0x80;
  player_plane_ptr[7] = 0xc0;
  uVar1 = select_hellcat_frame();
  *(undefined4 *)(player_plane_ptr + 4) = uVar1;
  uVar1 = FUN_0001cb30((short)DAT_0002458e,*(undefined4 *)(player_plane_ptr + 4));
  *(undefined4 *)(player_plane_ptr + 2) = uVar1;
  DAT_0002536e = FUN_0001cb30((short)DAT_00024592,*(undefined4 *)(player_plane_ptr + 4));
  pitch_cmd = 0;
  bomber_spawn_timer = 0x546;
  player_airspeed = 0;
  gear_target = 5;
  gear_anim = 5;
  deck_tail_up = 0;
  fuel_interval = 0x1c;
  DAT_0002729e = 0x1c;
  return;
}


// ==== player_touching_ground @ 0001b8c4 ====

undefined2 player_touching_ground(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  undefined2 local_16;
  undefined2 local_6;
  
  local_6 = 0;
  local_16 = (undefined2)((uint)player_plane_ptr >> 0x10);
  uVar2 = (undefined2)player_plane_ptr;
  sVar1 = wheel_clearance();
  sVar1 = *(short *)CONCAT22(local_16,uVar2) - sVar1;
  uVar2 = map_ptr_from_x();
  sVar3 = object_height(uVar2);
  if ((sVar1 < sVar3) || (sVar1 < 1)) {
    local_6 = 1;
  }
  return local_6;
}


// ==== arrester_wire_check @ 0001b92e ====

void arrester_wire_check(void)

{
  short sVar1;
  short sVar2;
  
  if ((599 < player_airspeed) && (deck_tail_up == 0)) {
    if (*(short *)(player_plane_ptr + 0x14) == -1) {
      sVar2 = *(short *)(player_plane_ptr + 2) + 0x18;
    }
    else {
      sVar2 = *(short *)(player_plane_ptr + 2) + -0x18;
    }
    wire_x_scan = *carrier_home_ptr + 0x46;
    for (sVar1 = 0; sVar1 < 4; sVar1 = sVar1 + 1) {
      if (((short)(wire_x_scan + -8) <= sVar2) && (sVar2 <= (short)(wire_x_scan + 8))) {
        *(undefined2 *)(player_plane_ptr + 0xc) = 7;
        deck_crew_signal = 4;
        DAT_000259ee = 0xffff;
        caught_wire_x = wire_x_scan;
        return;
      }
      wire_x_scan = wire_x_scan + 0x38;
    }
  }
  return;
}


// ==== engine_sound_off @ 0001b9bc ====

void engine_sound_off(void)

{
  engine_volume = 0;
  engine_volume_target = 0;
  return;
}


// ==== engine_sound_start @ 0001b9cc ====

void engine_sound_start(void)

{
  engine_volume = 0x28;
  engine_volume_target = 0x28;
  engine_period = 0x328;
  engine_period_base = 0x328;
  engine_boost = 0;
  return;
}


// ==== FUN_0001b9f0 @ 0001b9f0 ====

void FUN_0001b9f0(void)

{
  return;
}


// ==== player_ground_check @ 0001ba80 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void player_ground_check(void)

{
  bool bVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  
  sVar3 = player_plane_ptr[1];
  uVar2 = map_ptr_from_x();
  if (((own_carrier_x_start <= sVar3) && (sVar3 <= own_carrier_x_end)) && (turn_frame == 0)) {
    uVar5 = (undefined2)((uint)player_plane_ptr >> 0x10);
    uVar6 = SUB42(player_plane_ptr,0);
    sVar3 = object_height(uVar2);
    sVar4 = wheel_clearance();
    if (((short)(sVar4 + sVar3 + -4) <= *(short *)CONCAT22(uVar5,uVar6)) && (carrier_alive != 0)) {
      bVar1 = true;
      goto LAB_0001baf0;
    }
  }
  bVar1 = false;
LAB_0001baf0:
  sVar3 = wheel_clearance();
  if (((sVar3 < 0x37) && (player_plane_ptr[6] == 0)) &&
     (sVar3 = player_touching_ground(), sVar3 != 0)) {
    if (bVar1) {
      if ((player_plane_ptr[10] == -1) && (landing_attitude != 0)) {
        player_plane_ptr[6] = 1;
        DAT_000259ee = 0xffff;
        (*_sfx_screech)();
        uVar5 = (undefined2)((uint)player_plane_ptr >> 0x10);
        uVar6 = SUB42(player_plane_ptr,0);
        sVar3 = wheel_clearance();
        sVar4 = object_height(uVar2);
        *(short *)CONCAT22(uVar5,uVar6) = sVar4 + sVar3;
      }
      else {
        player_plane_ptr[0xc] = -player_plane_ptr[0xc];
        pitch_cmd = -pitch_cmd;
        *player_plane_ptr = *player_plane_ptr + 6;
        (*_sfx_screech)();
      }
    }
    else {
      player_plane_ptr[6] = 4;
      player_airspeed = player_plane_ptr[0xb] * 100;
      sVar3 = map_cell_is_sea(uVar2);
      if ((sVar3 == 0) &&
         ((sVar3 = map_cell_is_ship(uVar2), sVar3 == 0 || (0x13 < *player_plane_ptr)))) {
        uVar6 = 0;
        uVar5 = map_ptr_from_x(*player_plane_ptr,0);
        (*_spawn_explosion_at_cell)(uVar5,uVar6);
        (*_ground_impact_at_cell)(uVar2);
      }
      player_crash_update();
    }
  }
  return;
}


// ==== update_bomber_spawn_timer @ 0001bc02 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort update_bomber_spawn_timer(void)

{
  uint uVar1;
  ushort uVar2;
  short local_6;
  
  local_6 = 0x7fff - *(short *)(player_plane_ptr + 2);
  if (local_6 < 0) {
    local_6 = -local_6;
  }
  uVar2 = input_word & 0x30;
  if ((input_word & 0x30) == 0) {
    if ((((bomber_spawn_timer != 0) && (carrier_alive != 0)) && (carrier_hp != 0)) &&
       ((bomber_spawn_timer = bomber_spawn_timer + -1, bomber_spawn_timer == 0 && (0x1a00 < local_6)
        ))) {
      if ((*(short *)(player_plane_ptr + 2) < own_carrier_x_start) ||
         ((*(short *)(player_plane_ptr + 2) <= own_carrier_x_end &&
          (uVar1 = (*_thunk_FUN_000203be)(), (uVar1 & 0x8000) != 0)))) {
        uVar2 = (*_spawn_enemy_plane)(*(short *)(player_plane_ptr + 2) + -0x1800,1);
      }
      else {
        uVar2 = (*_spawn_enemy_plane)(*(short *)(player_plane_ptr + 2) + 0x1800,0xffff);
      }
    }
  }
  else if ((bomber_spawn_timer != 0) && (bomber_spawn_timer < 0x2ee)) {
    bomber_spawn_timer = 0x2ee;
  }
  return uVar2;
}


// ==== deck_crew_signal @ 0001bcce ====

void deck_crew_signal(void)

{
  short sVar1;
  
  if (DAT_000252b7 == '\0') {
    sVar1 = player_on_elevator();
    if (sVar1 == 0) {
      DAT_00025d9c = player_airspeed / 4;
      DAT_00025d9e = (short)(DAT_00025d9c * DAT_00025d9c * 2) / 100;
      DAT_00025da0 = *(short *)(player_plane_ptr + 2) - *carrier_home_ptr;
      if (DAT_00025da0 < 0) {
        DAT_00025da0 = -DAT_00025da0;
      }
      DAT_00025da0 = DAT_00025da0 + -0x10;
      if (*(short *)(player_plane_ptr + 2) < *carrier_home_ptr) {
        if (((DAT_00025da0 < DAT_00025d9e) && (*(short *)(player_plane_ptr + 0x14) == 1)) &&
           (0 < player_airspeed)) {
          deck_crew_signal = 4;
        }
      }
      else if (((DAT_00025da0 < DAT_00025d9e) && (*(short *)(player_plane_ptr + 0x14) == -1)) &&
              (0 < player_airspeed)) {
        deck_crew_signal = 4;
      }
    }
    else {
      deck_crew_signal = 5;
    }
  }
  else if (((short)(*(short *)(player_plane_ptr + 2) - own_carrier_x_start) < 0x136) &&
          (player_airspeed < 400)) {
    deck_crew_signal = 1;
  }
  else {
    deck_crew_signal = 0;
  }
  return;
}


// ==== deck_move @ 0001bdba ====

void deck_move(void)

{
  if (*(short *)(player_plane_ptr + 0xc) != 0) {
    *(short *)(player_plane_ptr + 0x16) = (short)(player_airspeed + 0x32) / 100;
    *(short *)(player_plane_ptr + 2) =
         *(short *)(player_plane_ptr + 0x16) * *(short *)(player_plane_ptr + 0x14) +
         *(short *)(player_plane_ptr + 2);
  }
  return;
}


// ==== player_flight_physics @ 0001bdfa ====

void player_flight_physics(void)

{
  short sVar1;
  
  if ((landing_attitude == 0) || (pitch_cmd != 600)) {
    sVar1 = pitch_cmd - pitch_smooth;
  }
  else {
    sVar1 = -800 - pitch_smooth;
  }
  pitch_smooth = sVar1 / 4 + pitch_smooth;
  if ((pitch_smooth < 0) || (pitch_bias < 0)) {
    FUN_00021cb0();
  }
  sVar1 = FUN_00021cc4();
  throttle_accel = throttle_accel - sVar1;
  if ((0 < player_plane_ptr[10]) && (player_airspeed < 1000)) {
    throttle_accel = throttle_accel - throttle_accel / 10;
  }
  FUN_00021ce2(*(undefined4 *)(&attitude_cos_table + turn_frame * 4));
  FUN_00021cec();
  FUN_00021cec();
  FUN_00021c9c();
  FUN_00021cd8();
  sVar1 = FUN_00021cc4();
  player_plane_ptr[0xb] = sVar1;
  player_plane_ptr[1] = player_plane_ptr[0xb] * player_plane_ptr[10] + player_plane_ptr[1];
  FUN_00021ce2();
  FUN_00021cec();
  FUN_00021cd8();
  sVar1 = FUN_00021cc4();
  player_plane_ptr[0xc] = sVar1;
  if ((player_airspeed < 1000) && (player_plane_ptr[6] == 0)) {
    if ((((byte)input_word & 1) == 0) &&
       (pitch_cmd = pitch_cmd - pitch_rate / 2, pitch_cmd < -0x1194)) {
      pitch_cmd = -0x1194;
    }
    player_plane_ptr[0xc] = player_plane_ptr[0xc] - (short)(1000 - player_airspeed) / 100;
  }
  *player_plane_ptr = player_plane_ptr[0xc] + *player_plane_ptr;
  if (*player_plane_ptr < 0x44d) {
    if (*player_plane_ptr < -4) {
      *player_plane_ptr = -4;
    }
  }
  else {
    *player_plane_ptr = 0x44c;
    pitch_cmd = -pitch_cmd;
    player_plane_ptr[0xc] = -(player_plane_ptr[0xc] / 2);
  }
  return;
}


// ==== player_flight_controls @ 0001bff4 ====

uint player_flight_controls(void)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  
  landing_attitude = 0;
  if ((input_word & 8) == 0) {
    sVar3 = 1;
  }
  else {
    sVar3 = -1;
  }
  pitch_bias = 0;
  uVar2 = input_word & 0xffff000f;
  if ((input_word & 0xf) == 0) {
    if (turn_frame == 0) {
      if (0 < pitch_cmd) {
        uVar2 = (uint)pitch_rate;
        pitch_cmd = pitch_cmd - pitch_rate;
        if (pitch_cmd < 0) {
          pitch_cmd = 0;
        }
        if (pitch_cmd < 0x1f5) {
          pitch_bias = -pitch_cmd;
          uVar2 = (uint)pitch_bias;
        }
      }
    }
    else {
      if (turn_frame < 7) {
        turn_frame = turn_frame + -1;
      }
      else {
        turn_step(0);
      }
      game_vbl_timer = 0;
      uVar2 = (int)(short)pitch_rate / 4 & 0xffff;
      pitch_cmd = pitch_cmd - (short)((int)(short)pitch_rate / 4);
      if (pitch_cmd < -0x8ca) {
        pitch_cmd = -0x8ca;
      }
      if ((0 < pitch_cmd) && (pitch_cmd < 0x1f5)) {
        pitch_bias = -pitch_cmd;
        uVar2 = (uint)pitch_bias;
      }
    }
    throttle_accel = throttle_accel - 1;
    if ((short)throttle_accel < 4) {
      throttle_accel = 4;
    }
    if (1000 < player_airspeed) {
      uVar2 = (uint)throttle_accel;
      player_airspeed = player_airspeed - throttle_accel;
      if (player_airspeed < 1000) {
        player_airspeed = 1000;
      }
    }
    engine_volume_target = 0x31;
    engine_period_base = 0x181;
    engine_boost = 0;
  }
  else {
    uVar2 = input_word & 0xffff000c;
    if ((input_word & 0xc) == 0) {
      engine_volume_target = 0x31;
      engine_period_base = 0x181;
      engine_boost = 0;
      if ((input_word & 2) == 0) {
        if ((input_word & 1) != 0) {
          if (*(short *)(player_plane_ptr + 0x14) == -1) {
            if ((pitch_cmd == 0) || (pitch_cmd < 600)) {
              pitch_cmd = pitch_rate + pitch_cmd;
              if (600 < pitch_cmd) {
                pitch_cmd = 600;
              }
            }
            else {
              pitch_cmd = pitch_cmd - pitch_rate;
              if (pitch_cmd < 600) {
                pitch_cmd = 600;
              }
            }
            uVar2 = (uint)pitch_rate;
            landing_attitude = 1;
          }
          else {
            uVar2 = (uint)pitch_rate;
            pitch_cmd = pitch_cmd - pitch_rate;
            if (pitch_cmd < -600) {
              uVar1 = (int)(short)(pitch_cmd + 600) / 2;
              uVar2 = uVar1 & 0xffff;
              pitch_cmd = pitch_cmd - (short)uVar1;
            }
            landing_attitude = 0;
          }
        }
      }
      else {
        engine_volume_target = 0x40;
        engine_period_base = 0x14f;
        engine_boost = 1;
        uVar2 = (uint)(ushort)(pitch_rate * 2);
        pitch_cmd = pitch_cmd + pitch_rate * -2;
        if (pitch_cmd < -0x1194) {
          pitch_cmd = -0x1194;
        }
      }
      pitch_bias = 0;
      if (turn_frame != 0) {
        if (turn_frame < 7) {
          turn_frame = turn_frame + -1;
        }
        else {
          uVar2 = turn_step(0);
        }
        game_vbl_timer = 0;
      }
    }
    else {
      if (*(short *)(player_plane_ptr + 0x14) == sVar3) {
        engine_boost = 1;
        if (turn_frame != 0) {
          if (turn_frame < 7) {
            turn_frame = turn_frame + -1;
          }
          else {
            turn_step(1);
          }
        }
        throttle_accel = throttle_accel + 1;
        if (8 < (short)throttle_accel) {
          throttle_accel = 8;
        }
        engine_volume_target = 0x40;
        engine_period_base = 0x14f;
        engine_boost = 1;
        player_airspeed = throttle_accel + player_airspeed;
        if (0x578 < player_airspeed) {
          player_airspeed = 0x578;
        }
      }
      else {
        turn_step(0);
      }
      uVar2 = input_word & 0xffff0003;
      if ((input_word & 3) == 0) {
        if (turn_frame == 0) {
          if (0 < pitch_cmd) {
            uVar2 = (uint)pitch_rate;
            pitch_cmd = pitch_cmd - pitch_rate;
            if (pitch_cmd < 0) {
              pitch_cmd = 0;
            }
            if (pitch_cmd < 0x1f5) {
              pitch_bias = -pitch_cmd;
              uVar2 = (uint)pitch_bias;
            }
          }
        }
        else {
          uVar2 = (int)(short)pitch_rate / 4 & 0xffff;
          pitch_cmd = pitch_cmd - (short)((int)(short)pitch_rate / 4);
          if (pitch_cmd < -0x8ca) {
            pitch_cmd = -0x8ca;
          }
          if ((0 < pitch_cmd) && (pitch_cmd < 0x1f5)) {
            pitch_bias = -pitch_cmd;
            uVar2 = (uint)pitch_bias;
          }
        }
      }
      else if ((input_word & 2) == 0) {
        if (player_airspeed < 0x3e9) {
          if (*(short *)(player_plane_ptr + 0x14) < 1) {
            uVar2 = (int)(short)pitch_rate / 8;
            sVar3 = (short)uVar2;
          }
          else {
            uVar2 = (int)(short)pitch_rate / 4;
            sVar3 = (short)uVar2;
          }
          pitch_cmd = sVar3 + pitch_cmd;
          uVar2 = uVar2 & 0xffff;
          if (3000 < pitch_cmd) {
            pitch_cmd = 3000;
          }
        }
        else {
          uVar2 = (uint)pitch_rate;
          pitch_cmd = pitch_rate + pitch_cmd;
          if (3000 < pitch_cmd) {
            pitch_cmd = 3000;
          }
        }
      }
      else if (turn_frame == 0) {
        uVar2 = (uint)pitch_rate;
        pitch_cmd = pitch_cmd - pitch_rate;
        if (pitch_cmd < -0x1194) {
          pitch_cmd = -0x1194;
        }
      }
      else {
        uVar2 = (int)(short)pitch_rate / 2 & 0xffff;
        pitch_cmd = pitch_cmd - (short)((int)(short)pitch_rate / 2);
        if (pitch_cmd < -0x1194) {
          pitch_cmd = -0x1194;
        }
      }
    }
  }
  return uVar2;
}


// ==== player_select_frames @ 0001c378 ====

void player_select_frames(void)

{
  undefined4 uVar1;
  short local_a;
  undefined2 uVar2;
  short local_6;
  
  local_6 = 0;
  uVar2 = 1;
  local_a = 9;
  DAT_00025372 = 0;
  if (((*(short *)(player_plane_ptr + 0xc) != 1) && (*(short *)(player_plane_ptr + 0xc) != 0xb)) &&
     (turn_frame == 0)) {
    local_a = (short)(pitch_cmd + 5000) / 500;
    local_6 = local_a;
  }
  if (((*(short *)(player_plane_ptr + 0xc) == 0) || (*(short *)(player_plane_ptr + 0xc) == 7)) ||
     ((*(short *)(player_plane_ptr + 0xc) == 4 || (deck_tail_up == 1)))) {
    if (turn_frame == 0) {
      if (*(short *)(player_plane_ptr + 0x14) == -1) {
        DAT_00025372 = *(undefined4 *)(&DAT_00025da2 + local_a * 4);
        DAT_00025376 = local_6 + 10;
      }
      else {
        DAT_00025372 = *(undefined4 *)(s_wh0awh0awh09wh09wh08wh08wh07wh07_00025df2 + local_a * 4);
        DAT_00025376 = local_6;
      }
      DAT_0002536a = FUN_0001cb30((short)DAT_0002458e,DAT_00025372,1);
    }
    else {
      uVar1 = select_hellcat_frame();
      *(undefined4 *)(player_plane_ptr + 8) = uVar1;
      DAT_000259ee = 0xffff;
    }
  }
  if (*(short *)(player_plane_ptr + 0xc) != 8) {
    uVar1 = select_hellcat_frame();
    *(undefined4 *)(player_plane_ptr + 8) = uVar1;
  }
  uVar1 = FUN_0001cb30((short)DAT_0002458e,*(undefined4 *)(player_plane_ptr + 8),uVar2);
  *(undefined4 *)(player_plane_ptr + 4) = uVar1;
  FUN_000204ec();
  DAT_0002536e = FUN_0001cb30((short)DAT_00024592,*(undefined4 *)(player_plane_ptr + 8));
  FUN_000204e4();
  return;
}


// ==== deck_throttle @ 0001c4e8 ====

short deck_throttle(void)

{
  short sVar1;
  short sVar2;
  
  gun_firing = 0;
  if ((input_word & 0xc) == 0) {
    engine_volume_target = 0x28;
    engine_period_base = 0x328;
    engine_boost = 0;
    throttle_accel = 0;
    player_airspeed = player_airspeed + -8;
    sVar1 = 0;
  }
  else {
    if ((input_word & 8) == 0) {
      sVar2 = 1;
    }
    else {
      sVar2 = -1;
    }
    sVar1 = *(short *)(player_plane_ptr + 0x14);
    if (sVar1 == sVar2) {
      engine_boost = 1;
      if (turn_frame == 0) {
        engine_volume_target = 0x40;
        engine_period_base = 0x14f;
        throttle_accel = throttle_accel + 1;
        if (8 < throttle_accel) {
          throttle_accel = 8;
        }
      }
      else {
        engine_volume_target = 0x28;
        engine_period_base = 0x328;
        turn_frame = turn_frame + -1;
      }
      player_airspeed = throttle_accel + player_airspeed;
      sVar1 = throttle_accel;
    }
    else {
      engine_boost = 0;
      engine_volume_target = 0x28;
      engine_period_base = 0x328;
      throttle_accel = 0;
      if ((player_airspeed == 0) && (turn_frame = turn_frame + 1, 6 < turn_frame)) {
        *(short *)(player_plane_ptr + 0x14) = -*(short *)(player_plane_ptr + 0x14);
        turn_frame = 5;
      }
      player_airspeed = player_airspeed + -8;
    }
  }
  deck_tail_up = 0;
  if ((600 < player_airspeed) && ((input_word & 1) == 0)) {
    deck_tail_up = 1;
  }
  if (player_airspeed < 0) {
    player_airspeed = 0;
  }
  else if (0x578 < player_airspeed) {
    player_airspeed = 0x578;
  }
  return sVar1;
}


// ==== deck_height_or_takeoff @ 0001c5f4 ====

void deck_height_or_takeoff(void)

{
  short *psVar1;
  short sVar2;
  undefined2 uVar3;
  short sVar4;
  
  psVar1 = player_plane_ptr;
  if ((player_plane_ptr[1] < own_carrier_x_start) || (own_carrier_x_end < player_plane_ptr[1])) {
    deck_crew_signal = 2;
    DAT_000252b7 = 0;
    player_plane_ptr[6] = 0;
    game_vbl_timer = DAT_00025e54;
  }
  else {
    sVar2 = wheel_clearance();
    uVar3 = map_ptr_from_x();
    sVar4 = object_height(uVar3);
    *psVar1 = sVar4 + sVar2;
  }
  return;
}


// ==== player_update @ 0001c660 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void player_update(void)

{
  short *psVar1;
  undefined2 uVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  undefined2 uStack_1a;
  
  game_vbl_timer = 100;
  player_fire_input();
  update_bomber_spawn_timer();
  if (_carrier_menu_active == 0) {
    if (player_airspeed == 0) {
      DAT_00026bda = 0;
    }
    uVar2 = SUB42(player_plane_ptr,0);
    uStack_1a = (undefined2)((uint)player_plane_ptr >> 0x10);
    switch(player_plane_ptr[6]) {
    case 0:
      if ((player_plane_ptr[9] < 0x60) || (player_plane_ptr[7] < 0)) {
        deck_crew_signal = 3;
        player_plane_ptr[6] = 4;
        player_airspeed = player_plane_ptr[0xb] * 100;
        player_crash_update();
      }
      else if (*player_plane_ptr < -6) {
        player_plane_ptr[6] = 6;
        next_wreck_explosion = 0;
        ticks_since_crash = 0;
        sink_subcounter = 0;
        deck_crew_signal = 3;
      }
      else {
        player_flight_controls();
        FUN_0001b9f0();
        player_flight_physics();
        player_ground_check();
        if (*player_plane_ptr < 0x51) {
          deck_crew_signal = 2;
        }
        else {
          deck_crew_signal = 3;
        }
        deck_crew_signal();
      }
      break;
    case 1:
      deck_throttle();
      deck_move();
      deck_height_or_takeoff();
      arrester_wire_check();
      deck_crew_signal();
      break;
    default:
      sVar3 = wheel_clearance();
      uVar4 = map_ptr_from_x();
      sVar5 = object_height(uVar4);
      *(short *)CONCAT22(uStack_1a,uVar2) = sVar5 + sVar3;
      if (*(short *)(carrier_home_ptr + 2) == 0) {
        player_plane_ptr[6] = 1;
      }
      break;
    case 4:
      engine_volume_target = 0x19;
      engine_period_base = 0x3c0;
      engine_boost = 0;
      gun_firing = 0;
      pitch_bias = 0;
      map_ptr_from_x();
      deck_crew_signal = 3;
      DAT_000259ee = 0xffff;
      player_crash_update();
      break;
    case 6:
      engine_volume_target = 0;
      sink_subcounter = sink_subcounter + 1;
      if (2 < sink_subcounter) {
        sink_subcounter = 0;
        *player_plane_ptr = *player_plane_ptr + -1;
      }
      pitch_cmd = pitch_cmd + -0xfa;
      if (pitch_cmd < -0x1194) {
        pitch_cmd = -0x1194;
      }
      wreck_explosions();
      respawn_timer();
      break;
    case 7:
      engine_volume_target = 0x28;
      engine_period_base = 0x328;
      sVar3 = wheel_clearance();
      uVar4 = map_ptr_from_x();
      sVar5 = object_height(uVar4);
      *(short *)CONCAT22(uStack_1a,uVar2) = sVar5 + sVar3;
      pitch_cmd = 0;
      pitch_bias = 0;
      DAT_00026bda = 0;
      player_airspeed = player_airspeed + -0x6e;
      if (player_airspeed < 0) {
        player_airspeed = 0;
        player_plane_ptr[6] = 1;
        DAT_000259ee = 0xffff;
      }
      deck_move();
      break;
    case 8:
      psVar1 = player_plane_ptr;
      psVar1[4] = 0x6863;
      psVar1[5] = 0x7235;
      if (player_plane_ptr[10] == -1) {
        psVar1 = player_plane_ptr;
        psVar1[4] = 0x6863;
        psVar1[5] = 0x7266;
      }
      attitude_frame_no = 0;
      uVar2 = map_ptr_from_x();
      sVar3 = map_cell_is_ship(uVar2);
      if (sVar3 == 0) {
        sVar3 = wheel_clearance();
        *player_plane_ptr = sVar3;
      }
      else {
        uStack_1a = (undefined2)((uint)player_plane_ptr >> 0x10);
        uVar4 = SUB42(player_plane_ptr,0);
        sVar3 = wheel_clearance();
        sVar5 = object_height(uVar2);
        *(short *)CONCAT22(uStack_1a,uVar4) = sVar5 + sVar3;
      }
      DAT_00026bd4 = DAT_00026bd4 + 1;
      if ((DAT_00026bd4 & 3) == 0) {
        FUN_0001cae0(6,*player_plane_ptr + 0xb);
      }
      wreck_explosions();
      respawn_timer();
      break;
    case 9:
    }
    update_gear_target();
    player_select_frames();
  }
  else {
    throttle_accel = 0;
    player_airspeed = 0;
  }
  zoom_request = 8;
  if (0xba < *player_plane_ptr) {
    zoom_request = 1;
  }
  return;
}


// ==== map_ptr_from_x @ 0001c982 ====

uint map_ptr_from_x(int param_1)

{
  uint local_8;
  
  if (param_1 < 0) {
    param_1._0_2_ = 0;
  }
  local_8 = DAT_00024578 + (short)(param_1._0_2_ / 8 << 1);
  if (DAT_0002457c <= local_8) {
    local_8 = DAT_0002457c - 2;
  }
  return local_8;
}


// ==== fire_button_debounce @ 0001c9ca ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fire_button_debounce(void)

{
  short sVar1;
  
  DAT_00026be2 = DAT_00026be2 + 1;
  sVar1 = (*_thunk_FUN_0002044c)();
  if ((sVar1 != 0) && (DAT_00026bdc == 0)) {
    DAT_00026bde = DAT_00026be2;
  }
  if (DAT_00026be2 < DAT_00026bde + 10) {
    if ((sVar1 == 0) && (DAT_00026bdc != 0)) {
      DAT_00027d4c = 1;
    }
  }
  else if (sVar1 != 0) {
    DAT_00027d4a = 1;
  }
  if (sVar1 == 0) {
    DAT_00026bde = 0;
  }
  DAT_00026bdc = sVar1;
  return;
}


// ==== build_input_word @ 0001ca32 ====

void build_input_word(void)

{
  ushort uVar1;
  
  uVar1 = FUN_0001cb20();
  input_word._1_1_ = 0;
  if (DAT_00027d4c != 0) {
    input_word._1_1_ = 0x20;
    DAT_00027d4c = 0;
    DAT_00027d4a = 0;
  }
  if (DAT_00027d4a != 0) {
    input_word._1_1_ = (byte)input_word | 0x10;
    DAT_00027d4a = 0;
  }
  if ((uVar1 & 1) != 0) {
    input_word._1_1_ = (byte)input_word | 1;
  }
  if ((uVar1 & 2) != 0) {
    input_word._1_1_ = (byte)input_word | 2;
  }
  if ((uVar1 & 4) != 0) {
    input_word._1_1_ = (byte)input_word | 8;
  }
  if ((uVar1 & 8) != 0) {
    input_word._1_1_ = (byte)input_word | 4;
  }
  input_word._0_1_ = 0;
  return;
}


// ==== set_screen_flash @ 0001cab4 ====

void set_screen_flash(undefined4 param_1)

{
  sky_flash_count = param_1._0_2_;
  sky_flash_color = param_1._2_2_;
  return;
}


// ==== rand_mod @ 0001cac8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint rand_mod(uint param_1)

{
  uint uVar1;
  
  uVar1 = (*_thunk_FUN_000203be)();
  return (uVar1 & 0xffff) / (param_1 >> 0x10) << 0x10 | (uVar1 & 0xffff) % (param_1 >> 0x10);
}


// ==== FUN_0001cae0 @ 0001cae0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001cae0(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  
  uVar1 = (*_thunk_FUN_000203be)();
  FUN_000154cc((int)(short)((uVar1 & 7) + param_2._0_2_) << 0x10,0);
  return;
}


// ==== FUN_0001cb20 @ 0001cb20 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001cb20(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001cb20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_read_joystick_dirs)();
  return;
}


// ==== FUN_0001cb30 @ 0001cb30 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001cb30(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001cb30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_000204f4)();
  return;
}


// ==== map_cell_is_ship @ 0001cb34 ====

bool map_cell_is_ship(ushort *param_1)

{
  bool bVar1;
  
  if ((DAT_00024578 < param_1) && (param_1 < (ushort *)(DAT_0002457c + -2))) {
    bVar1 = (*param_1 & 3) == 1;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}


// ==== map_cell_is_sea @ 0001cb74 ====

bool map_cell_is_sea(ushort *param_1)

{
  bool bVar1;
  
  if ((DAT_00024578 < param_1) && (param_1 < (ushort *)(DAT_0002457c + -2))) {
    bVar1 = (*param_1 & 3) == 0;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}


// ==== map_cell_is_island @ 0001cbb2 ====

bool map_cell_is_island(ushort *param_1)

{
  bool bVar1;
  
  if ((DAT_00024578 < param_1) && (param_1 < (ushort *)(DAT_0002457c + -2))) {
    bVar1 = (*param_1 & 3) == 2;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}


// ==== ship_num_from_map_ptr @ 0001cbf2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 ship_num_from_map_ptr(undefined4 param_1)

{
  short sVar1;
  short local_8;
  
  sVar1 = map_cell_is_ship(param_1);
  if (sVar1 == 0) {
    (*_thunk_FUN_00021dce)(s_Not_over_a_ship_in_ShipNum__0001cc76);
  }
  else {
    sVar1 = (short)param_1 - (short)DAT_00024578;
    local_8 = 0;
    do {
      if ((*(short *)(&ship_ptr_list)[local_8] <= sVar1) &&
         (sVar1 <= *(short *)((&ship_ptr_list)[local_8] + 2))) {
        return CONCAT22((short)((uint)(local_8 * 4) >> 0x10),local_8);
      }
      local_8 = local_8 + 1;
    } while (local_8 < 5);
    (*_thunk_FUN_00021dce)(s_COULDN_T_FIND_A_SHIP_in_ShipNum__0001cc93);
  }
  return 1;
}


// ==== FUN_0001ccb6 @ 0001ccb6 ====

void FUN_0001ccb6(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_00022b7c(0);
  if (((iVar1 < 400000) && (param_1._0_2_ != 0)) && (*(int *)(DAT_00026e76 + 0x34) != 0)) {
    DAT_00026d6a = 1;
    FUN_00022f1c(*(undefined4 *)(DAT_00026e76 + 0x34));
  }
  FUN_00022f28();
  return;
}


// ==== keyboard_commands @ 0001ccf6 ====

/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void keyboard_commands(void)

{
  uint uVar1;
  char cVar6;
  short sVar4;
  undefined2 uVar5;
  undefined4 uVar2;
  int iVar3;
  ushort *puVar7;
  undefined1 uVar8;
  
  _DAT_00026eac = 0;
  uVar8 = 1;
LAB_0001ccfa:
  while( true ) {
    (*_thunk_FUN_000207d8)();
    if ((bool)uVar8) {
      return;
    }
    uVar1 = (*_thunk_FUN_000207e4)();
    _DAT_00026eac = uVar1 & 0x7fffffff;
    cVar6 = (*_thunk_FUN_00020700)((short)uVar1);
    iVar3 = DAT_00026ec4;
    if ((_DAT_00026eac & 0x80000) == 0) break;
    if (cVar6 == 'r') {
      ticker_message = 0;
      clear_ticker();
      uVar8 = 0;
      FUN_000173e6();
      abort_to_rank_select = 0xff;
      session_over = 0xff;
    }
    else if (cVar6 == 's') {
      sound_off = ~sound_off;
      uVar8 = sound_off == 0;
      if (!(bool)uVar8) {
        (*_sound_stop_all)();
      }
    }
    else if (cVar6 == 'f') {
      invert_updown = ~invert_updown;
      uVar8 = invert_updown == 0;
    }
    else if (cVar6 == 'g') {
      uVar8 = 0;
      if (player_state == 1) {
        (*_sound_stop_all)();
        uVar8 = 0;
        load_save_game_dialog();
        rebuild_game_display();
        (*_input_queue_clear)();
      }
    }
    else if (cVar6 == 'l') {
      uVar8 = 0;
      if (demo_mode == 0) {
        (*_sound_stop_all)();
        (*_thunk_FUN_000134ae)();
        (*_free_sounds)();
        (*_thunk_FUN_00011256)();
        DAT_00026c90 = 0;
        sVar4 = load_save_game_dialog();
        uVar8 = sVar4 == 0;
        if ((bool)uVar8) {
          DAT_00026c90 = 1;
          load_dash_shapes();
          (*_mission_briefing_screen)();
          (*_thunk_FUN_0001edaa)();
          (*_setup_level_display)();
          (*_load_ship_shapes)();
          FUN_0001535a();
          (*_load_sounds)();
          not_in_game = 0;
          DAT_00026c90 = 0;
          uVar8 = 1;
          (*_logic_tick)();
          (*_input_queue_clear)();
        }
        else {
          load_dash_shapes();
          (*_load_sounds)();
          rebuild_game_display();
          (*_input_queue_clear)();
        }
      }
    }
    else {
      if (cVar6 == 'b') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
        halt_unimplemented();
      }
      if (cVar6 == 'c') {
        uVar8 = 0;
        (**(code **)(DAT_00026e6e + -0x48))();
      }
      else {
        if (cVar6 != 'v') break;
        uVar8 = DAT_00027d32 == 0;
        (*_format_string)(DAT_00027d34);
        (*_ticker_start_message)();
      }
    }
  }
  if (cVar6 == '\x1b') {
    paused = ~paused;
    uVar8 = paused == 0;
    if (!(bool)uVar8) {
      (*_sound_stop_all)();
    }
    goto LAB_0001ccfa;
  }
  if (cVar6 == 'o') {
    if (cheat_state == 1) {
      cheat_state = 2;
      uVar8 = 0;
      goto LAB_0001ccfa;
    }
  }
  else if (cVar6 == 'l') {
    if (cheat_state == 2) {
      cheat_state = 3;
      uVar8 = 0;
      goto LAB_0001ccfa;
    }
  }
  else {
    if (cVar6 != 'n') {
      if (cVar6 == 'i') {
        uVar8 = 1;
        if (cheat_state == 0) goto LAB_0001ccfa;
        if (cheat_state == 5) {
          pitch_rate = pitch_rate + 0x32;
          uVar8 = pitch_rate == 0;
          goto LAB_0001ccfa;
        }
        if (cheat_state == 3) {
          cheat_state = 4;
          uVar8 = 0;
          goto LAB_0001ccfa;
        }
        cheat_state = 0;
      }
      if (cVar6 == 'k') {
        uVar8 = 0;
        if (cheat_state == 5) {
          pitch_rate = pitch_rate + -0x32;
          uVar8 = pitch_rate == 0;
        }
      }
      else if (cVar6 == 'f') {
        uVar8 = 0;
        if (cheat_state == 5) {
          player_fuel = 0x80;
          uVar8 = 0;
        }
      }
      else if (cVar6 == 'p') {
        uVar8 = 0;
        if (cheat_state == 5) {
          lives = lives + '\x01';
          uVar8 = lives == '\0';
        }
      }
      else if (DAT_00026eaf == 'Y') {
        uVar8 = 0;
        if (cheat_state == 5) {
          ticker_message = 0;
          uVar8 = 1;
        }
      }
      else if (cVar6 == ' ') {
        uVar8 = 0;
        if (cheat_state == 5) {
          uVar5 = (**(code **)(DAT_00026ec4 + -0xd8))();
          uVar5 = (**(code **)(iVar3 + -0xd8))(uVar5);
          uVar2 = (**(code **)(iVar3 + -0xd8))(uVar5);
          iVar3 = (**(code **)(iVar3 + -0xd8))(uVar2);
          uVar8 = iVar3 == 0;
          (*_format_string)(iVar3);
          (*_ticker_start_message)();
        }
      }
      else if (DAT_00026eaf == '_') {
        uVar8 = 0;
        if (cheat_state == 5) {
          sVar4 = 0;
          puVar7 = &beach_right_offsets;
          while (*puVar7 <= render_player_x >> 2) {
            sVar4 = sVar4 + 1;
            puVar7 = puVar7 + 1;
          }
          uVar8 = sVar4 == 0;
          (*_format_string)();
          (*_ticker_start_message)();
        }
      }
      else if (cVar6 == 'q') {
        uVar8 = cheat_state == 5;
        if ((bool)uVar8) {
          quit_program = 0xff;
          session_over = 0xff;
        }
      }
      else if (cVar6 == 'm') {
        uVar8 = 0;
        if (cheat_state == 5) {
          if (ordnance_count == -1) {
            ordnance_count = (&ordnance_per_weapon)[weapon_type];
            uVar8 = ordnance_count == '\0';
            (*_hud_set_ammo_drum)();
          }
          else {
            ordnance_count = -1;
            uVar8 = 0;
          }
        }
      }
      else if (cVar6 == 'r') {
        uVar8 = cheat_state == 5;
        if ((bool)uVar8) {
          (*_clear_projectiles)();
        }
      }
      else {
        if (cVar6 != 'c') {
          if (cVar6 == '8') {
            uVar8 = cheat_state == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            gravity = gravity + 0x1000;
          }
          else if (cVar6 == '2') {
            uVar8 = cheat_state == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            gravity = gravity + -0x1000;
          }
          else if (cVar6 == '4') {
            uVar8 = cheat_state == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            gravity = gravity + -0x100;
          }
          else if (cVar6 == '6') {
            uVar8 = cheat_state == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            gravity = gravity + 0x100;
          }
          uVar8 = 0;
          if ((cVar6 == 'd') && (uVar8 = 0, cheat_state == 5)) {
            player_oil = 0x80;
            player_state = 0;
            invulnerable = ~invulnerable;
            uVar8 = invulnerable == 0;
          }
          goto LAB_0001ccfa;
        }
        if (cheat_state == 0) {
          cheat_state = 1;
          uVar8 = 0;
        }
        else {
          uVar8 = 0;
          if (cheat_state == 5) {
            weapon_type = weapon_type + 1;
            uVar8 = 0;
            if (weapon_type == 3) {
              weapon_type = 0;
              uVar8 = 1;
            }
          }
        }
      }
      goto LAB_0001ccfa;
    }
    if (cheat_state == 4) {
      cheat_state = 5;
      uVar8 = 0;
      goto LAB_0001ccfa;
    }
  }
  cheat_state = 0;
  uVar8 = 1;
  goto LAB_0001ccfa;
}


// ==== enemy_plane_despawn_far @ 0001d18c ====

undefined2 enemy_plane_despawn_far(undefined2 *param_1)

{
  short local_8;
  undefined2 local_6;
  
  local_6 = 0;
  if ((*(byte *)((int)param_1 + 3) & 0x10) != 0) {
    local_8 = *(short *)(player_plane_ptr + 2) - param_1[0x10];
    if (local_8 < 0) {
      local_8 = -local_8;
    }
    if (0xa28 < local_8) {
      *param_1 = 0;
      param_1[1] = 0;
      local_6 = 1;
    }
  }
  return local_6;
}


// ==== build_enemy_plane_frame_tables @ 0001d1ea ====

void build_enemy_plane_frame_tables(void)

{
  undefined4 uVar1;
  short local_8;
  short local_6;
  
  local_6 = 0;
  do {
    uVar1 = FUN_0001cb30(DAT_0002459a,*(undefined4 *)(&DAT_00025ea8 + local_6 * 4));
    *(undefined4 *)(&enemy_plane_frames + local_6 * 4) = uVar1;
    uVar1 = FUN_0001cb30(DAT_0002459a,*(undefined4 *)(&DAT_00025f18 + local_6 * 4));
    *(undefined4 *)(&enemy_plane_frames + (short)(local_6 + 0x1c) * 4) = uVar1;
    uVar1 = FUN_0001cb30(DAT_00024586,*(undefined4 *)(&DAT_00025f88 + local_6 * 4));
    *(undefined4 *)(&enemy_plane_frames_8th + local_6 * 4) = uVar1;
    uVar1 = FUN_0001cb30(DAT_00024586,*(undefined4 *)(&DAT_00025ff8 + local_6 * 4));
    *(undefined4 *)(&enemy_plane_frames_8th + (short)(local_6 + 0x1c) * 4) = uVar1;
    local_8 = 0;
    do {
      uVar1 = FUN_0001cb30(DAT_0002458a,
                           (int)(short)((local_8 + 0x31) * 0x100) +
                           (*(uint *)(&DAT_00026068 + local_6 * 4) & 0xffff00ff));
      *(undefined4 *)(&DAT_000273ac + (short)(local_6 + local_8 * 0x38) * 4) = uVar1;
      uVar1 = FUN_0001cb30(DAT_0002458a,
                           (int)(short)((local_8 + 0x31) * 0x100) +
                           (*(uint *)(&DAT_000260d8 + local_6 * 4) & 0xffff00ff));
      *(undefined4 *)(&DAT_000273ac + (short)(local_6 + local_8 * 0x38 + 0x1c) * 4) = uVar1;
      local_8 = local_8 + 1;
    } while (local_8 < 3);
    local_6 = local_6 + 1;
  } while (local_6 < 0x1c);
  return;
}


// ==== enemy_plane_set_sprite @ 0001d35a ====

void enemy_plane_set_sprite(int param_1)

{
  undefined2 local_6;
  
  local_6 = *(short *)(param_1 + 0x16);
  if (((*(byte *)(param_1 + 3) & 4) != 0) && (*(short *)(param_1 + 0x16) == 0)) {
    local_6 = 0x1a;
  }
  if (*(short *)(param_1 + 0x14) == -1) {
    *(short *)(param_1 + 0x30) = local_6;
  }
  else {
    *(short *)(param_1 + 0x30) = local_6 + 0x1c;
  }
  return;
}


// ==== enemy_plane_relation_to_player @ 0001d3b4 ====

void enemy_plane_relation_to_player(int param_1)

{
  ushort uVar1;
  short sVar2;
  
  uVar1 = *(short *)(param_1 + 0x20) - *(short *)(player_plane_ptr + 2);
  if (*(short *)(player_plane_ptr + 0x14) == *(short *)(param_1 + 0x14)) {
    *(undefined2 *)(param_1 + 4) = 1;
    if ((-1 < (short)(uVar1 ^ *(ushort *)(player_plane_ptr + 0x14))) &&
       (*(undefined2 *)(param_1 + 4) = 3, *(short *)(param_1 + 0x10) == 0)) {
      *(undefined2 *)(param_1 + 0x10) = 0x226;
    }
  }
  else {
    *(undefined2 *)(param_1 + 4) = 2;
    if ((short)uVar1 < 0) {
      *(undefined2 *)(param_1 + 4) = 4;
    }
  }
  sVar2 = *(short *)(param_1 + 0x20) - *(short *)(player_plane_ptr + 2);
  *(short *)(param_1 + 0x28) = sVar2;
  if (sVar2 < 0) {
    *(short *)(param_1 + 0x28) = -*(short *)(param_1 + 0x28);
  }
  return;
}


// ==== enemy_plane_chase_queue @ 0001d476 ====

void enemy_plane_chase_queue(void)

{
  short local_a;
  short local_8;
  short local_6;
  
  local_6 = 0;
  do {
    local_8 = 1;
    if (((&DAT_0002517c)[local_6 * 0x1a] != 0) && ((&DAT_0002517e)[local_6 * 0x1a] == 1)) {
      for (local_a = 0; local_a < local_6; local_a = local_a + 1) {
        if ((&DAT_0002517e)[local_a * 0x1a] == 1) {
          if (*(short *)(&DAT_000251a2 + local_a * 0x34) <
              *(short *)(&DAT_000251a2 + local_6 * 0x34)) {
            local_8 = local_8 + 1;
          }
          else {
            (&DAT_00025186)[local_a * 0x1a] = (&DAT_00025186)[local_a * 0x1a] + 1;
          }
        }
      }
      (&DAT_00025186)[local_6 * 0x1a] = local_8;
    }
    local_6 = local_6 + 1;
  } while (local_6 < 4);
  return;
}


// ==== enemy_plane_manoeuvre_step @ 0001d530 ====

void enemy_plane_manoeuvre_step(int param_1)

{
  short sVar1;
  
  *(undefined2 *)(param_1 + 0x10) = 0;
  sVar1 = *(short *)(param_1 + 0x32);
  *(short *)(param_1 + 0x32) = *(short *)(param_1 + 0x32) + -1;
  if (sVar1 < 1) {
    *(undefined2 *)(param_1 + 0x32) = 2;
    *(short *)(param_1 + 0x16) = *(short *)(param_1 + 0x16) + 1;
  }
  return;
}


// ==== enemy_plane_manoeuvre @ 0001d562 ====

uint enemy_plane_manoeuvre(int param_1)

{
  short sVar1;
  bool bVar2;
  undefined4 in_D0;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  bVar2 = false;
  sVar1 = player_plane_ptr[6];
  if ((player_plane_ptr[6] == 0) && ((*(ushort *)(param_1 + 2) & 3) != 0)) {
    *(undefined2 *)(param_1 + 0x24) = *player_plane_ptr;
  }
  if (((((turn_frame != 0) || (sVar1 == 1)) || (player_plane_ptr[6] != 0)) ||
      ((*(short *)(param_1 + 0x16) < 0x13 ||
       ((*(short *)(param_1 + 4) != 1 && (*(short *)(param_1 + 4) != 3)))))) ||
     (uVar3 = CONCAT22((short)((uint)in_D0 >> 0x10),*(ushort *)(param_1 + 2)) & 0xffff0003,
     (*(ushort *)(param_1 + 2) & 3) == 0)) {
    uVar3 = enemy_plane_manoeuvre_step(param_1);
    if (*(short *)(param_1 + 0x16) < 0x1a) {
      if (*(short *)(param_1 + 0x16) == 0xe) {
        *(short *)(param_1 + 0x14) = -*(short *)(param_1 + 0x14);
        *(short *)(param_1 + 0x16) = *(short *)(param_1 + 0x16) + 1;
      }
      else if (((*(short *)(param_1 + 0x16) == 0x14) &&
               (uVar3 = CONCAT22((short)(uVar3 >> 0x10),*(ushort *)(param_1 + 2)) & 0xffff0003,
               (*(ushort *)(param_1 + 2) & 3) != 0)) && (player_plane_ptr[6] == 0)) {
        if (*(short *)(param_1 + 0x1a) < 3) {
          uVar4 = (uint)*(short *)(param_1 + 4);
          uVar3 = uVar4;
          if (uVar4 < 5) {
            uVar3 = CONCAT22((short)((uVar4 << 1) >> 0x10),
                             *(undefined2 *)
                              ((int)&switchD_0001d75a::switchdataD_0001d742 +
                              (int)(short)(uVar4 << 1)));
            switch(uVar4) {
            case 1:
              if (((0 < turn_frame) && (turn_frame < 6)) && (*(short *)(param_1 + 0x10) == 0)) {
                iVar5 = (int)(short)(*(short *)(param_1 + 0x28) * 100);
                uVar4 = iVar5 / (int)*(short *)(param_1 + 0x1c);
                uVar3 = iVar5 % (int)*(short *)(param_1 + 0x1c) << 0x10 | uVar4 & 0xffff;
                *(short *)(param_1 + 0x18) = (short)uVar4;
              }
              bVar2 = true;
              break;
            case 2:
              if ((0 < turn_frame) && (turn_frame < 6)) {
                bVar2 = true;
              }
              break;
            case 3:
              bVar2 = true;
              break;
            case 4:
              if (*(short *)(param_1 + 0x10) == 0) {
                iVar6 = (int)(short)(*(short *)(param_1 + 0x28) * 100);
                iVar5 = (int)(short)(player_airspeed + *(short *)(param_1 + 0x1c));
                uVar4 = iVar6 / iVar5;
                uVar3 = iVar6 % iVar5 << 0x10 | uVar4 & 0xffff;
                *(short *)(param_1 + 0x18) = (short)uVar4;
              }
              bVar2 = true;
            }
          }
          if (((bVar2) && (sVar1 != 1)) && (*(short *)(param_1 + 0x10) == 0)) {
            sVar1 = *(short *)(param_1 + 0x16) + -0xd;
            uVar3 = CONCAT22((short)(uVar3 >> 0x10),sVar1 * 2);
            *(short *)(param_1 + 0x16) = *(short *)(param_1 + 0x16) + sVar1 * -2;
            *(short *)(param_1 + 0x1a) = *(short *)(param_1 + 0x1a) + 1;
          }
        }
        else {
          *(undefined2 *)(param_1 + 0x1a) = 0;
          *(undefined2 *)(param_1 + 0x10) = 0x226;
        }
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x16) = 0;
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf7;
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x16) = 0;
    *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf7;
  }
  return uVar3;
}


// ==== enemy_plane_move @ 0001d796 ====

uint enemy_plane_move(ushort *param_1)

{
  short sVar2;
  short sVar3;
  uint uVar1;
  int extraout_A0;
  ushort *puVar4;
  
  if (((*param_1 & 0x14) == 0) &&
     (((*(short *)(player_plane_ptr + 0xc) == 4 || (*(short *)(player_plane_ptr + 0xc) == 8)) ||
      (*(short *)(player_plane_ptr + 0xc) == 6)))) {
    param_1[0xf] = 0x6a4;
  }
  FUN_00021ce2(*(undefined4 *)(&attitude_cos_table + (short)param_1[0xb] * 4));
  FUN_00021cec();
  sVar2 = FUN_00021cc4();
  *(short *)(extraout_A0 + 0x20) = sVar2 + *(short *)(extraout_A0 + 0x20);
  if (((*param_1 & 0x14) == 0) && ((*(byte *)((int)param_1 + 3) & 4) == 0)) {
    if (*(short *)(player_plane_ptr + 0xc) == 1) {
      param_1[0x12] = 0x46;
    }
    if ((short)param_1[0x12] < 0x21) {
      param_1[0x12] = 0x21;
    }
  }
  sVar2 = param_1[0x12] - param_1[0x13];
  if (sVar2 < 0) {
    sVar2 = -sVar2;
  }
  if (100 < sVar2) {
    sVar2 = 100;
  }
  if ((*param_1 & 4) != 0) {
    if ((short)param_1[0x12] < (short)param_1[0x13]) {
      param_1[0x13] = (short)param_1[0x11] / 100 + param_1[0x13];
      param_1[0x11] = param_1[0x11] - 10;
    }
    else if ((short)param_1[0x13] < (short)param_1[0x12]) {
      param_1[0x13] = param_1[0x12];
    }
  }
  if ((short)param_1[0x12] < (short)param_1[0x13]) {
    puVar4 = param_1;
    sVar3 = rand_mod();
    puVar4[0x13] = puVar4[0x13] - (sVar3 + *(short *)(&climb_step_table + (sVar2 / 0x14) * 2));
  }
  else if ((short)param_1[0x13] < (short)param_1[0x12]) {
    puVar4 = param_1;
    sVar3 = rand_mod();
    puVar4[0x13] = sVar3 + *(short *)(&climb_step_table + (sVar2 / 0x14) * 2) + puVar4[0x13];
  }
  uVar1 = *param_1 & 0xffff0014;
  if ((((*param_1 & 0x14) == 0) && (param_1[0xc] != 0)) &&
     (param_1[0xc] = param_1[0xc] - 1, (short)param_1[0xc] < 1)) {
    *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
    param_1[0xc] = 0;
  }
  if (((*(byte *)((int)param_1 + 3) & 8) != 0) && (*param_1 == 2)) {
    uVar1 = enemy_plane_manoeuvre(param_1);
  }
  return uVar1;
}


// ==== enemy_ai_chase @ 0001d9c6 ====

void enemy_ai_chase(int param_1)

{
  short sVar1;
  
  switch(*(undefined2 *)(param_1 + 4)) {
  case 1:
    if (*(short *)(param_1 + 0x28) < 0xa0) {
      if (((turn_frame < 1) || (5 < turn_frame)) ||
         ((player_plane_ptr[6] == 1 || (*(short *)(param_1 + 0x18) != 0)))) {
        if (((*(short *)(param_1 + 0x28) < 0xa0) && (*(short *)(param_1 + 0x18) == 0)) &&
           (*(short *)(param_1 + 0xc) == 1)) {
          *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 8 | 2;
        }
        else {
          *(undefined2 *)(param_1 + 0x12) = 0;
          *(short *)(param_1 + 0x24) = *player_plane_ptr;
          *(short *)(param_1 + 0x1e) = player_airspeed + *(short *)(param_1 + 0xc) * -0x46;
        }
      }
      else {
        *(short *)(param_1 + 0x18) =
             *(short *)(param_1 + 0xc) * 2 +
             (short)(*(short *)(param_1 + 0x28) * 100) / *(short *)(param_1 + 0x1c);
      }
    }
    else if (*(short *)(param_1 + 0x16) == 0) {
      *(short *)(param_1 + 0x1e) = player_airspeed + *(short *)(param_1 + 0x28);
      if (*(short *)(param_1 + 0xc) == 1) {
        *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0xc) * 0x50 + *(short *)(param_1 + 0x1e);
      }
      else {
        *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + *(short *)(param_1 + 0xc) * -0x50;
      }
    }
    break;
  case 2:
    if (((player_plane_ptr[6] == 0) && (0 < turn_frame)) && (turn_frame < 0xb)) {
      *(undefined2 *)(param_1 + 0x1e) = enemy_min_speed;
    }
    else {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
    break;
  case 3:
    if (*(short *)(param_1 + 0x28) < 0x600) {
      *(short *)(param_1 + 0x10) = *(short *)(param_1 + 0x10) + -1;
      if ((*(short *)(param_1 + 0x10) < 1) ||
         (((0 < turn_frame && (turn_frame < 6)) || (player_plane_ptr[6] == 1)))) {
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
        *(undefined2 *)(param_1 + 0x10) = 0;
      }
      else if (*(short *)(param_1 + 6) == 1) {
        *(undefined2 *)(param_1 + 6) = 0;
        if (*(short *)(param_1 + 0x18) == 0) {
          sVar1 = rand_mod();
          *(short *)(param_1 + 0x18) = sVar1 + 8;
        }
        *(undefined2 *)(param_1 + 0x10) = 0x226;
      }
      else {
        *(short *)(param_1 + 0x1e) = player_airspeed - *(short *)(param_1 + 0x28) / 4;
        sVar1 = DAT_00027db6 * 0x46;
        DAT_00027db6 = DAT_00027db6 + 1;
        *(short *)(param_1 + 0x1e) = sVar1 + *(short *)(param_1 + 0x1e);
        if (*(short *)(param_1 + 0x26) == *(short *)(param_1 + 0x24)) {
          sVar1 = rand_mod();
          *(short *)(param_1 + 0x24) = sVar1 * 10 + 0x23;
        }
      }
    }
    else {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
    break;
  case 4:
    if (player_plane_ptr[6] == 0) {
      *(undefined2 *)(param_1 + 0x1e) = enemy_min_speed;
      if (*(short *)(param_1 + 0x26) < *player_plane_ptr) {
        *(short *)(param_1 + 0x24) = *player_plane_ptr + -0x20;
      }
      else {
        *(short *)(param_1 + 0x24) = *player_plane_ptr + 0x20;
      }
      *(short *)(param_1 + 0x18) =
           (short)(*(short *)(param_1 + 0x28) * 100) /
           (short)(player_plane_ptr[0xb] + *(short *)(param_1 + 0x1c));
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
  }
  return;
}


// ==== enemy_ai_attack @ 0001dccc ====

void enemy_ai_attack(int param_1)

{
  bool bVar1;
  short *psVar2;
  short sVar3;
  short local_6;
  
  if (*(short *)(param_1 + 4) == 1) {
    if ((turn_frame == 0) && (player_plane_ptr[6] != 1)) {
      if (*(short *)(param_1 + 0x28) < 0x83) {
        if (*(short *)(param_1 + 0x28) < 0x82) {
          *(short *)(param_1 + 0x1e) = player_airspeed + -0x32;
        }
      }
      else {
        *(short *)(param_1 + 0x1e) = player_airspeed + 0x32;
      }
    }
    else {
      *(undefined2 *)(param_1 + 2) = 9;
      *(short *)(param_1 + 0x18) = *(short *)(param_1 + 0x28) / (*(short *)(param_1 + 0x1c) / 100);
    }
    *(short *)(param_1 + 0x24) = *player_plane_ptr;
    local_6 = *player_plane_ptr - *(short *)(param_1 + 0x26);
    if (local_6 < 0) {
      local_6 = -local_6;
    }
    if ((player_plane_ptr[6] == 0) && (*(short *)(param_1 + 2) == 2)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (((((bVar1) && (*(short *)(param_1 + 0xc) == 1)) && (local_6 < 8)) &&
        ((*(short *)(param_1 + 0x16) == 0 && (*(short *)(param_1 + 0x28) < 0xa0)))) &&
       ((player_plane_ptr[10] == *(short *)(param_1 + 0x14) &&
        ((short)(*(short *)(param_1 + 0x20) - player_plane_ptr[1] ^ player_plane_ptr[10]) < 0)))) {
      *(undefined2 *)(param_1 + 0x12) = 1;
      psVar2 = player_plane_ptr;
      if (((invulnerable == 0) && (*(short *)(param_1 + 0x26) == *player_plane_ptr)) &&
         ((DAT_00027296 != 0 && (player_plane_ptr[8] = player_plane_ptr[8] + -1, psVar2[8] < 1)))) {
        player_plane_ptr[9] = player_plane_ptr[9] + -8;
        psVar2 = player_plane_ptr;
        sVar3 = rand_mod();
        psVar2[7] = psVar2[7] - sVar3;
        psVar2 = player_plane_ptr;
        sVar3 = rand_mod();
        psVar2[8] = sVar3 + 6;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x12) = 0;
    }
  }
  else {
    *(undefined2 *)(param_1 + 2) = 1;
  }
  return;
}


// ==== enemy_ai_carrier_bomber @ 0001dea4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void enemy_ai_carrier_bomber(undefined2 *param_1)

{
  bool bVar1;
  short sVar2;
  
  bVar1 = false;
  if (param_1[2] == 3) {
    if (param_1[3] == 1) {
      param_1[3] = 0;
      if (param_1[0xc] == 0) {
        sVar2 = rand_mod();
        param_1[0xc] = sVar2 + 8;
      }
      param_1[8] = 0x113;
    }
    if (0x96 < (short)param_1[0x14]) {
      param_1[0x14] = 0xf0;
    }
    if (((short)param_1[0x14] < 0x96) &&
       (param_1[0x14] = param_1[0x14] + -0x96, param_1[0x13] == param_1[0x12])) {
      sVar2 = rand_mod();
      param_1[0x12] = sVar2 * 10 + 0x23;
    }
    param_1[0xf] = player_airspeed - param_1[0x14];
  }
  else if ((param_1[10] == -1) && ((short)param_1[0x10] < (short)(own_carrier_x_start + -500))) {
    *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
  }
  else if ((param_1[10] == 1) && ((short)(own_carrier_x_end + 500) < (short)param_1[0x10])) {
    *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
  }
  if (((param_1[10] == -1) && (own_carrier_x_end < (short)param_1[0x10])) &&
     ((short)(param_1[0x10] - own_carrier_x_end) < 1000)) {
    param_1[0x12] = 0x14;
  }
  else if (((param_1[10] == 1) && ((short)param_1[0x10] < own_carrier_x_start)) &&
          ((short)(own_carrier_x_start - param_1[0x10]) < 1000)) {
    param_1[0x12] = 0x14;
  }
  if (((param_1[10] == -1) && (own_carrier_x_end < (short)param_1[0x10])) ||
     ((param_1[10] == 1 && ((short)param_1[0x10] < own_carrier_x_start)))) {
    bVar1 = true;
  }
  if (bVar1) {
    if ((param_1[0x13] == 0x14) && (param_1[0xb] == 0)) {
      DAT_00025506 = 2;
      DAT_000254f6 = 0;
      DAT_000254f2 = (short)param_1[0xe] * 0x28f;
      _DAT_000254e8 = (int)(short)(param_1[0x13] + 0xf) << 0x10;
      _enemy_bomb_object = (int)(short)param_1[0x10] << 0x10;
      DAT_00025503 = *(char *)((int)param_1 + 0x15);
      if (DAT_00025503 == -1) {
        DAT_000254f2 = (short)param_1[0xe] * -0x28f;
      }
      DAT_00025504._0_1_ = 0xff;
      DAT_00025502 = 0;
      *param_1 = 2;
      param_1[0xf] = enemy_max_speed / 2;
      param_1[0x12] = 0x3c;
      param_1[1] = 0x10;
      bomber_spawn_timer = 500;
    }
  }
  else {
    param_1[8] = param_1[8] + -1;
    if ((short)param_1[8] < 1) {
      *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
      param_1[8] = 0;
    }
  }
  return;
}


// ==== enemy_ai_escape @ 0001e17a ====

void enemy_ai_escape(int param_1)

{
  short sVar1;
  int iVar2;
  
  sVar1 = enemy_plane_despawn_far(param_1);
  if ((sVar1 == 0) && (*(short *)(param_1 + 0x16) == 0)) {
    if (*(short *)(param_1 + 4) == 3) {
      if (*(short *)(param_1 + 6) == 1) {
        *(undefined2 *)(param_1 + 6) = 0;
        if (*(short *)(param_1 + 0x18) == 0) {
          iVar2 = param_1;
          sVar1 = rand_mod();
          *(short *)(iVar2 + 0x18) = sVar1 + 8;
        }
        *(undefined2 *)(param_1 + 0x10) = 0x226;
      }
      else if ((*(short *)(param_1 + 0x26) == *(short *)(param_1 + 0x24)) &&
              (*(short *)(param_1 + 0x28) < 0xa0)) {
        sVar1 = rand_mod();
        *(short *)(param_1 + 0x24) = sVar1 * 10 + 0x19;
      }
    }
    else if (*(short *)(param_1 + 4) == 1) {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
  }
  return;
}


// ==== enemy_plane_falling @ 0001e244 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void enemy_plane_falling(undefined2 *param_1)

{
  ushort uVar2;
  uint uVar1;
  short sVar3;
  undefined2 uVar4;
  
  sVar3 = 0x80 - param_1[4];
  uVar2 = (*_thunk_FUN_000203be)();
  if ((short)(uVar2 & 0x3f) < sVar3) {
    FUN_0001cae0(((short)(0x80 - param_1[4]) >> 3) + 1,param_1[0x13] + 10);
  }
  if (param_1[0x13] == param_1[0x12]) {
    uVar1 = map_ptr_from_x();
    uVar4 = (undefined2)uVar1;
    sVar3 = map_cell_is_sea(uVar4);
    if ((sVar3 != 0) && ((short)param_1[0xe] < 300)) {
      DAT_00026be6 = DAT_00026be6 + 1;
      if (1 < DAT_00026be6) {
        DAT_00026be6 = 0;
        param_1[0x12] = param_1[0x12] + -1;
      }
      param_1[0xe] = param_1[0xe] + 0x18;
    }
    param_1[0xe] = param_1[0xe] + -0x23;
    (*_thunk_FUN_00011a84)(0x14);
    if (500 < (short)param_1[0xe]) {
      (*_ground_impact_at_cell)(uVar4);
    }
    (*_thunk_FUN_000152ac)(param_1[0x13] + 3);
    if ((short)param_1[0xe] < 100) {
      enemy_planes_destroyed = enemy_planes_destroyed + '\x01';
      sVar3 = map_cell_is_island(uVar4);
      if (((sVar3 == 0) || (uVar1 < DAT_00024578)) || (DAT_0002457c <= uVar1)) {
        if ((param_1[1] != 4) && (param_1[1] != 0x10)) {
          zeros_airborne = zeros_airborne + -1;
        }
        *param_1 = 0;
        param_1[1] = 0;
      }
      else {
        *param_1 = 0x10;
        param_1[0xf] = 6;
        param_1[0xe] = 0x1e;
        param_1[1] = 0;
      }
    }
  }
  return;
}


// ==== enemy_plane_wreck_burning @ 0001e3e8 ====

uint enemy_plane_wreck_burning(undefined2 *param_1)

{
  uint uVar1;
  int iVar2;
  
  if (param_1[10] == -1) {
    param_1[0x18] = 0x1b;
  }
  else {
    param_1[0x18] = 0x37;
  }
  param_1[0xe] = param_1[0xe] + -1;
  if (param_1[0xe] == 0) {
    param_1[0xf] = param_1[0xf] + -1;
    param_1[0xe] = param_1[0xf] * 5;
  }
  if ((short)param_1[0xf] < 2) {
    iVar2 = (int)wreck_count;
    uVar1 = iVar2 * 2;
    wreck_count = wreck_count + 1;
    (&wreck_list)[iVar2] = param_1[10] * param_1[0x10];
    if ((param_1[1] != 4) && (param_1[1] != 0x10)) {
      zeros_airborne = zeros_airborne + -1;
    }
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    uVar1 = (ushort)param_1[0xe] & 0xffff0003;
    if ((param_1[0xe] & 3) == 0) {
      uVar1 = FUN_0001cae0(param_1[0xf],6);
    }
  }
  return uVar1;
}


// ==== FUN_0001e4c8 @ 0001e4c8 ====

void FUN_0001e4c8(void)

{
  return;
}


// ==== spawn_enemy_plane @ 0001e4d0 ====

void spawn_enemy_plane(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  
  sVar4 = -1;
  bVar2 = false;
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    if ((&enemy_planes)[sVar3 * 0x1a] == 0) {
      sVar4 = sVar3;
    }
    if (((*(byte *)((int)&DAT_0002517c + sVar3 * 0x34 + 1) & 4) != 0) &&
       ((&enemy_planes)[sVar3 * 0x1a] != 0)) {
      bVar2 = true;
    }
  }
  if ((sVar4 != -1) && (((param_1._0_2_ != 0 && (!bVar2)) || (param_1._0_2_ == 0)))) {
    iVar1 = (int)sVar4;
    (&enemy_planes)[iVar1 * 0x1a] = 2;
    (&DAT_0002518e)[iVar1 * 0x1a] = param_2._2_2_;
    (&DAT_0002519a)[iVar1 * 0x1a] = param_1._2_2_;
    (&DAT_0002519e)[iVar1 * 0x1a] = 0x32;
    (&DAT_00025198)[iVar1 * 0x1a] = enemy_min_speed;
    (&DAT_00025196)[iVar1 * 0x1a] = enemy_min_speed;
    (&DAT_00025182)[iVar1 * 0x1a] = 0xf0;
    sVar3 = rand_mod();
    (&DAT_00025184)[iVar1 * 0x1a] = sVar3 + 5;
    (&DAT_00025180)[iVar1 * 0x1a] = 0;
    (&DAT_0002517e)[iVar1 * 0x1a] = 0;
    (&DAT_00025192)[iVar1 * 0x1a] = 0;
    (&DAT_00025190)[iVar1 * 0x1a] = 0;
    (&DAT_00025186)[iVar1 * 0x1a] = 0;
    if (param_1._0_2_ == 0) {
      zeros_airborne = zeros_airborne + 1;
      (&DAT_0002517c)[iVar1 * 0x1a] = 1;
      (&DAT_000251a0)[iVar1 * 0x1a] = param_2._0_2_;
    }
    else {
      (&DAT_0002517c)[iVar1 * 0x1a] = 4;
      (&DAT_000251a0)[iVar1 * 0x1a] = 0x32;
    }
  }
  return;
}


// ==== clear_enemy_planes @ 0001e608 ====

void clear_enemy_planes(void)

{
  undefined2 *local_10;
  ushort local_8;
  short local_6;
  
  local_6 = 0;
  do {
    local_10 = &enemy_planes + local_6 * 0x1a;
    for (local_8 = 0; local_8 < 0x34; local_8 = local_8 + 1) {
      *(undefined1 *)local_10 = 0;
      local_10 = (undefined2 *)((int)local_10 + 1);
    }
    local_6 = local_6 + 1;
  } while (local_6 < 4);
  return;
}


// ==== enemy_plane_speed_governor @ 0001e64e ====

void enemy_plane_speed_governor(short *param_1)

{
  if (*param_1 == 2) {
    if (param_1[0xf] < enemy_min_speed) {
      param_1[0xf] = enemy_min_speed;
    }
    if (enemy_max_speed < param_1[0xf]) {
      param_1[0xf] = enemy_max_speed;
    }
    if (param_1[0xe] < param_1[0xf]) {
      param_1[0xe] = (short)(param_1[0xf] - param_1[0xe]) / 2 + 5 + param_1[0xe];
      if (enemy_max_speed < param_1[0xe]) {
        param_1[0xe] = enemy_max_speed;
      }
    }
    else if ((param_1[0xf] < param_1[0xe]) &&
            (param_1[0xe] = param_1[0xe] - ((short)(param_1[0xe] - param_1[0xf]) / 2 + -5),
            param_1[0xe] < enemy_min_speed)) {
      param_1[0xe] = enemy_min_speed;
    }
  }
  return;
}


// ==== enemy_plane_ai_flying @ 0001e728 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int enemy_plane_ai_flying(int param_1)

{
  ushort uVar2;
  int iVar1;
  short sVar3;
  undefined2 uVar4;
  
  sVar3 = 0x80 - *(short *)(param_1 + 8);
  uVar2 = (*_thunk_FUN_000203be)();
  if ((short)(uVar2 & 0x3f) < sVar3) {
    FUN_0001cae0(((short)(0x80 - *(short *)(param_1 + 8)) >> 3) + 1,*(short *)(param_1 + 0x26) + 0xb
                );
  }
  iVar1 = (int)(short)(*(ushort *)(param_1 + 2) & 0xfff7);
  uVar4 = (undefined2)param_1;
  if (iVar1 == 1) {
    iVar1 = enemy_ai_chase(uVar4);
  }
  else if (iVar1 == 2) {
    iVar1 = enemy_ai_attack(uVar4);
  }
  else if (iVar1 == 4) {
    iVar1 = enemy_ai_carrier_bomber(uVar4);
  }
  else {
    iVar1 = iVar1 + -0x10;
    if (iVar1 == 0) {
      iVar1 = enemy_ai_escape(uVar4);
    }
  }
  return iVar1;
}


// ==== update_enemy_planes @ 0001e7d6 ====

void update_enemy_planes(void)

{
  short sVar1;
  short *psVar2;
  int iVar3;
  short sVar4;
  
  DAT_00027db6 = 0;
  sVar4 = 0;
  do {
    iVar3 = (int)sVar4;
    psVar2 = &enemy_planes + iVar3 * 0x1a;
    if (*psVar2 != 0) {
      enemy_plane_relation_to_player(psVar2);
      enemy_plane_chase_queue();
      sVar1 = *psVar2;
      if (sVar1 == 1) {
        FUN_0001e4c8(psVar2);
      }
      else if (sVar1 == 2) {
        enemy_plane_ai_flying(psVar2);
        if (((*(byte *)((int)&DAT_0002517c + iVar3 * 0x34 + 1) & 4) == 0) &&
           ((short)(&DAT_0002519e)[iVar3 * 0x1a] < 0x21)) {
          (&DAT_0002519e)[iVar3 * 0x1a] = 0x21;
        }
      }
      else if (sVar1 == 4) {
        enemy_plane_falling(psVar2);
      }
      else if ((sVar1 != 8) && (sVar1 == 0x10)) {
        enemy_plane_wreck_burning(psVar2);
      }
      enemy_plane_speed_governor(psVar2);
      if (*psVar2 != 0x10) {
        enemy_plane_move(psVar2);
      }
      enemy_plane_set_sprite(psVar2);
    }
    sVar4 = sVar4 + 1;
  } while (sVar4 < 4);
  return;
}


// ==== sfx_init @ 0001e8b8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_init(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  if (DAT_00027db8 == 0) {
    sfx_vbl_count = 0;
    sVar1 = 3;
    puVar2 = &sfx_channels;
    do {
      *puVar2 = 0;
      *(undefined2 *)(puVar2 + 2) = 0;
      *(undefined4 *)((int)puVar2 + 0x16) = 0xffffffff;
      puVar2[1] = 0;
      puVar2 = (undefined4 *)((int)puVar2 + 0x1e);
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    _DAT_00dff096 = 0xf;
    _DAT_00dff09e = 0xff;
    DAT_00027e36 = _DAT_00000070;
    _DAT_00000070 = audio_interrupt_handler;
    _DAT_00dff09c = 0x780;
    _DAT_00dff09a = 0x8780;
    DAT_00027e42 = 2;
    DAT_00027e43 = 0x1e;
    DAT_00027e44 = s_SoundFX_IntHandler_00026154;
    DAT_00027e4c = sfx_vbl_server;
    (**(code **)(DAT_00026ec4 + -0xa8))();
    DAT_00027db8 = 1;
  }
  return 0;
}


// ==== sfx_shutdown @ 0001e94c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_shutdown(void)

{
  if (DAT_00027db8 != 0) {
    (*_sfx_stop_all_channels)();
    (**(code **)(DAT_00026e6e + -0xc6))();
    (**(code **)(DAT_00026ec4 + -0xae))();
    _DAT_00dff09a = 0x780;
    _DAT_00dff096 = 0xf;
    _DAT_00000070 = DAT_00027e36;
    DAT_00027db8 = 0;
  }
  return 0;
}


// ==== sfx_play_sample_struct @ 0001e992 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_play_sample_struct(void)

{
  undefined4 uVar1;
  int in_A0;
  
  if (in_A0 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    (*_sfx_start_channel)();
    uVar1 = 0;
  }
  return uVar1;
}


// ==== FUN_0001e9de @ 0001e9de ====

undefined4 FUN_0001e9de(void)

{
  undefined4 in_D0;
  
  do {
    if (DAT_00027e64 < '\0') {
      return in_D0;
    }
  } while (DAT_00bfe0ff < '\0');
  return in_D0;
}


// ==== FUN_0001e9f4 @ 0001e9f4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001e9f4(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_00027e64 = 0;
  DAT_00027e65 = 0xff;
  (*_sfx_stop_channel)();
  (**(code **)(DAT_00026e6e + -0xc6))();
  DAT_00027e66 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001ea18 @ 0001ea18 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001ea18(void)

{
  (*_sfx_stop_channel)();
  DAT_00027e65 = 0;
  DAT_00027e66 = 0;
  return;
}


// ==== sfx_start_channel @ 0001ea28 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_start_channel(void)

{
  int iVar1;
  uint in_D0;
  short sVar2;
  undefined4 in_D1;
  short extraout_D1w;
  short extraout_D1w_00;
  short sVar3;
  undefined2 unaff_D2w;
  undefined2 unaff_D3w;
  undefined2 unaff_D4w;
  int in_A0;
  undefined4 extraout_A0;
  undefined4 extraout_A0_00;
  undefined4 uVar4;
  
  if (in_A0 != 0) {
    if ((short)in_D1 == 6) {
      FUN_0001e9f4();
    }
    sVar2 = (*_sfx_channel_busy)();
    uVar4 = extraout_A0;
    sVar3 = extraout_D1w;
    if (sVar2 != 0) {
      (*_sfx_stop_channel)();
      uVar4 = extraout_A0_00;
      sVar3 = extraout_D1w_00;
    }
    _DAT_00dff09c = (ushort)(1 << ((ushort)(sVar3 + 7) & 0x1f));
    _DAT_00dff09a = _DAT_00dff09c | 0x8000;
    iVar1 = (int)(short)(sVar3 * 0x1e);
    *(short *)((int)&DAT_00027dc8 + iVar1) = (short)(in_D0 >> 1);
    *(undefined2 *)((int)&DAT_00027dca + iVar1) = unaff_D2w;
    *(undefined2 *)((int)&DAT_00027dcc + iVar1) = unaff_D3w;
    *(undefined2 *)((int)&DAT_00027dcc + iVar1 + 2) = 0;
    *(undefined2 *)((int)&DAT_00027dd0 + iVar1) = unaff_D4w;
    *(undefined4 *)((int)&sfx_channels + iVar1) = uVar4;
    *(undefined4 *)((int)&DAT_00027dd4 + iVar1) = 0xffffffff;
    *(undefined2 *)((int)&DAT_00027dc6 + iVar1) = 1;
  }
  return in_D1;
}


// ==== sfx_stop_all_channels @ 0001eab4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sfx_stop_all_channels(void)

{
  short sVar1;
  
  do {
    sVar1 = (*_sfx_stop_channel)();
  } while (sVar1 != 0);
  return;
}


// ==== sfx_stop_channel @ 0001eac0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 sfx_stop_channel(void)

{
  int iVar1;
  short sVar2;
  uint in_D0;
  undefined4 in_D1;
  
  sVar2 = (short)in_D0;
  iVar1 = (int)(short)(sVar2 * 0x1e);
  _DAT_00dff09a = 0x80 << (in_D0 & 0x3f);
  *(undefined2 *)((int)&DAT_00027dc6 + iVar1) = 0;
  _DAT_00dff096 = 1 << (in_D0 & 0x3f);
  *(undefined4 *)((int)&sfx_channels + iVar1) = 0;
  *(undefined2 *)((int)&DAT_00027dd2 + iVar1) = 0xffff;
  *(undefined4 *)((int)&DAT_00027dd4 + iVar1) = 0xffffffff;
  *(undefined2 *)(&DAT_00dff0a8 + (short)(sVar2 << 4)) = 0;
  *(undefined4 *)((int)&DAT_00027dc2 + iVar1) = sfx_vbl_count;
  *(undefined2 *)(&DAT_00dff0a6 + (short)(sVar2 << 4)) = 0x7c;
  if (sVar2 == 2) {
    DAT_00027e66 = 0;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== sfx_channel_busy @ 0001eb2e ====

undefined8 sfx_channel_busy(void)

{
  undefined4 uVar1;
  undefined4 in_D1;
  
  uVar1 = 0;
  if (*(int *)((int)&sfx_channels + (int)(short)((short)in_D1 * 0x1e)) != 0) {
    uVar1 = 0xffffffff;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== sfx_set_period_volume @ 0001eb4c ====

void sfx_set_period_volume(void)

{
  int iVar1;
  short in_D0w;
  short in_D1w;
  short unaff_D2w;
  
  iVar1 = (int)(short)(in_D0w * 0x1e);
  if (-1 < in_D1w) {
    *(short *)(&DAT_00dff0a6 + (short)(in_D0w << 4)) = in_D1w;
  }
  if (-1 < unaff_D2w) {
    *(undefined4 *)((int)&DAT_00027dd4 + iVar1) = 0xffffffff;
    *(short *)((int)&DAT_00027dcc + iVar1) = unaff_D2w;
    *(undefined2 *)((int)&DAT_00027dcc + iVar1 + 2) = 0;
    *(short *)(&DAT_00dff0a8 + (short)(in_D0w << 4)) = unaff_D2w;
  }
  return;
}


// ==== sfx_set_volume_slide @ 0001eb94 ====

void sfx_set_volume_slide(void)

{
  short in_D0w;
  int in_D1;
  undefined4 unaff_D2;
  
  *(undefined4 *)((int)&DAT_00027dd8 + (int)(short)(in_D0w * 0x1e)) = unaff_D2;
  *(int *)((int)&DAT_00027dd4 + (int)(short)(in_D0w * 0x1e)) = in_D1 << 0x10;
  return;
}


// ==== audio_interrupt_handler @ 0001ebaa ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 audio_interrupt_handler(void)

{
  short sVar1;
  ushort uVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  uint uVar3;
  short sVar4;
  short sVar5;
  uint uVar6;
  int *piVar7;
  undefined1 *puVar8;
  
  *(undefined4 *)(&DAT_00026168 + (short)(DAT_00027e68 * 4)) = DAT_00027e6a;
  piVar7 = &sfx_channels;
  puVar8 = &DAT_00dff0a0;
  uVar2 = _DAT_00dff01c & _DAT_00dff01e;
  uVar3 = 7;
  sVar4 = 1;
  sVar5 = 3;
  uVar6 = 0;
  do {
    if ((CONCAT22((short)((uint)in_D0 >> 0x10),uVar2) & 0xffff0780 & 1 << (uVar3 & 0x1f)) != 0) {
      if ((*piVar7 == 0) ||
         ((-1 < *(short *)(piVar7 + 5) &&
          (sVar1 = *(short *)(piVar7 + 5), *(short *)(piVar7 + 5) = sVar1 + -1, sVar1 < 1)))) {
        if (sVar5 == 1) {
          DAT_00027e66 = 0;
        }
        uVar6 = uVar6 | 1 << (uVar3 & 0x1f);
        _DAT_00dff096 = sVar4;
        *(undefined4 *)((int)piVar7 + 0x16) = 0xffffffff;
        *(undefined2 *)(puVar8 + 8) = 0;
        *(undefined4 *)((int)piVar7 + 0xe) = 0;
        piVar7[1] = sfx_vbl_count;
        *piVar7 = 0;
      }
      uVar6 = uVar6 | 1 << (uVar3 & 0x1f);
    }
    uVar3 = (uint)(ushort)((short)uVar3 + 1);
    sVar4 = sVar4 << 1;
    piVar7 = (int *)((int)piVar7 + 0x1e);
    puVar8 = puVar8 + 0x10;
    sVar5 = sVar5 + -1;
  } while (sVar5 != -1);
  if ((short)uVar6 != 0) {
    _DAT_00dff09c = (short)uVar6;
  }
  _DAT_00dff09a = 0xc000;
  return CONCAT44(in_D0,in_D1);
}


// ==== sfx_vbl_server @ 0001ec64 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_vbl_server(void)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  sfx_vbl_count = sfx_vbl_count + 1;
  puVar4 = &sfx_channels;
  puVar5 = (undefined4 *)&DAT_00dff0a0;
  uVar2 = 1;
  sVar3 = 3;
  DAT_00027e6e = _DAT_00dff01c & 0x780;
  DAT_00027e70 = 0x8000;
  do {
    if ((*(short *)(puVar4 + 2) != 0) && (1 < sfx_vbl_count - puVar4[1])) {
      if ((DAT_00027e65 != '\0') && (sVar3 == 1)) {
        DAT_00027e64 = 0xff;
        DAT_00027e66 = 0xff;
      }
      *puVar5 = *puVar4;
      *(undefined2 *)(puVar5 + 1) = *(undefined2 *)((int)puVar4 + 10);
      *(undefined2 *)((int)puVar5 + 6) = *(undefined2 *)(puVar4 + 3);
      *(undefined2 *)(puVar5 + 2) = *(undefined2 *)((int)puVar4 + 0xe);
      *(undefined2 *)(puVar4 + 5) = *(undefined2 *)((int)puVar4 + 0x12);
      DAT_00027e70 = uVar2 | DAT_00027e70;
      *(undefined2 *)(puVar4 + 2) = 0;
    }
    if (-1 < *(short *)((int)puVar4 + 0x16)) {
      iVar1 = *(int *)((int)puVar4 + 0xe);
      if (iVar1 == *(int *)((int)puVar4 + 0x16)) {
LAB_0001ed32:
        iVar1 = *(int *)((int)puVar4 + 0x16);
        *(undefined4 *)((int)puVar4 + 0x16) = 0xffffffff;
      }
      else if (iVar1 < *(int *)((int)puVar4 + 0x16)) {
        iVar1 = *(int *)((int)puVar4 + 0x1a) + iVar1;
        if (*(int *)((int)puVar4 + 0x16) <= iVar1) goto LAB_0001ed32;
      }
      else {
        iVar1 = iVar1 - *(int *)((int)puVar4 + 0x1a);
        if (iVar1 <= *(int *)((int)puVar4 + 0x16)) goto LAB_0001ed32;
      }
      *(int *)((int)puVar4 + 0xe) = iVar1;
      *(short *)(puVar5 + 2) = (short)((uint)iVar1 >> 0x10);
    }
    uVar2 = uVar2 << 1;
    puVar4 = (undefined4 *)((int)puVar4 + 0x1e);
    puVar5 = puVar5 + 4;
    sVar3 = sVar3 + -1;
    if (sVar3 == -1) {
      if ((char)DAT_00027e70 != '\0') {
        _DAT_00dff096 = DAT_00027e70;
      }
      _DAT_00dff09a = 0x8780;
      return 0;
    }
  } while( true );
}


// ==== FUN_0001ed7a @ 0001ed7a ====

void FUN_0001ed7a(void)

{
  undefined1 *in_A0;
  
  *in_A0 = 0xff;
  in_A0[2] = 0xff;
  in_A0[4] = 0xff;
  in_A0[6] = 0xff;
  in_A0[8] = 0xff;
  in_A0[10] = 0xff;
  in_A0[0xc] = 0xff;
  in_A0[0xe] = 0xff;
  in_A0[0x10] = 0xff;
  DAT_00027ea8 = 0x3c;
  DAT_00027eaa = 0x54;
  return;
}


// ==== FUN_0001edaa @ 0001edaa ====

void FUN_0001edaa(void)

{
  FUN_0001ed7a();
  FUN_0001ed7a();
  return;
}


// ==== hud_set_ammo_drum @ 0001edbc ====

void hud_set_ammo_drum(void)

{
  DAT_00027e7a = (ordnance_count / 10) * -8 + 0x50;
  DAT_00027e7c = ((ushort)ordnance_count % 10) * -8 + 0x50;
  DAT_00027e8a = 0xff;
  DAT_00027e9e = 0xff;
  return;
}


// ==== hud_set_lives_drum @ 0001edea ====

void hud_set_lives_drum(void)

{
  ushort uVar1;
  byte bVar2;
  
  bVar2 = lives;
  if ((char)lives < '\0') {
    bVar2 = 0;
  }
  uVar1 = (ushort)bVar2;
  if (9 < bVar2) {
    uVar1 = 9;
  }
  DAT_00027e7e = uVar1 * -8 + 0x59;
  DAT_00027e8c = 0xff;
  DAT_00027ea0 = 0xff;
  return;
}


// ==== draw_dashboard @ 0001ee16 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 draw_dashboard(void)

{
  short sVar1;
  bool bVar2;
  short sVar3;
  ushort uVar4;
  byte bVar5;
  short sVar6;
  ushort uVar7;
  
  sVar1 = *back_view;
  (*_own_blitter)();
  (*_clip_dashboard)();
  DAT_00027eac = CONCAT11(0xff,(undefined1)DAT_00027eac);
  if (((player_state != 0) && (player_state != 1)) && (player_state != 7)) {
    DAT_00027eac = 0;
  }
  draw_enemy_warning_light();
  sVar6 = player_oil - 0x60;
  if ((short)player_oil < 0x60) {
    sVar6 = 0;
  }
  uVar7 = sVar6 * 2 & 0xfffc;
  if ((player_state < 2) && (engine_boost != 0)) {
    uVar7 = uVar7 + 0x18;
  }
  if (uVar7 != DAT_00027ea8) {
    if ((short)uVar7 < (short)DAT_00027ea8) {
      DAT_00027ea8 = DAT_00027ea8 - 4;
    }
    else {
      DAT_00027ea8 = DAT_00027ea8 + 4;
    }
  }
  uVar7 = DAT_00027ea8;
  sVar6 = 0xc;
  if ((DAT_00027eac != 0) && (player_oil < 0x74)) {
    sVar6 = 0x10;
    sVar3 = DAT_00027eae + -1;
    bVar2 = DAT_00027eae < 1;
    DAT_00027eae = sVar3;
    if ((sVar3 == 0 || bVar2) && (sVar6 = 0xc, sVar3 != 0)) {
      DAT_00027eae = 10;
    }
  }
  if ((sVar6 != *(short *)(&dash_cache + sVar1)) ||
     (DAT_00027ea8 != *(ushort *)(&DAT_00027e82 + sVar1))) {
    *(short *)(&dash_cache + sVar1) = sVar6;
    *(ushort *)(&DAT_00027e82 + sVar1) = uVar7;
    (*_draw_shape_automask)();
    (*_draw_shape_automask)();
    (*_draw_shape_automask)();
  }
  uVar7 = player_fuel;
  if ((short)player_fuel < 0) {
    uVar7 = 0;
  }
  uVar7 = uVar7 >> 1;
  if (0x58 < uVar7) {
    uVar7 = 0x58;
  }
  uVar7 = uVar7 & 0xfffc;
  if ((uVar7 == 0) && (DAT_00027eac != 0)) {
    uVar7 = (*_thunk_FUN_000203be)();
    uVar7 = uVar7 >> 0xd & 4;
  }
  if (uVar7 != DAT_00027eaa) {
    if ((short)uVar7 < (short)DAT_00027eaa) {
      DAT_00027eaa = DAT_00027eaa - 4;
    }
    else {
      DAT_00027eaa = DAT_00027eaa + 4;
    }
  }
  uVar7 = DAT_00027eaa;
  sVar6 = 0xc;
  if ((DAT_00027eac != 0) && ((short)player_fuel < 0x41)) {
    sVar6 = 0x10;
    sVar3 = DAT_00027eb0 + -1;
    bVar2 = DAT_00027eb0 < 1;
    DAT_00027eb0 = sVar3;
    if ((sVar3 == 0 || bVar2) && (sVar6 = 0xc, sVar3 != 0)) {
      DAT_00027eb0 = 8;
    }
  }
  if ((sVar6 != *(short *)(&DAT_00027e84 + sVar1)) ||
     (DAT_00027eaa != *(ushort *)(&DAT_00027e86 + sVar1))) {
    *(short *)(&DAT_00027e84 + sVar1) = sVar6;
    *(ushort *)(&DAT_00027e86 + sVar1) = uVar7;
    (*_draw_shape_automask)();
    (*_draw_shape_automask)();
    (*_draw_shape_automask)();
  }
  if (weapon_type != *(short *)(&DAT_00027e88 + sVar1)) {
    *(short *)(&DAT_00027e88 + sVar1) = weapon_type;
    (*_blit_shape)();
  }
  if ((ordnance_count == 0xff) || ((ushort)ordnance_count != *(ushort *)(&DAT_00027e8a + sVar1))) {
    sVar6 = -1;
    uVar7 = (ushort)ordnance_count;
    do {
      uVar4 = uVar7;
      sVar6 = sVar6 + 1;
      uVar7 = uVar4 - 10;
    } while (9 < uVar4);
    uVar7 = uVar4 * -8 + 0x50;
    uVar4 = sVar6 * -8 + 0x50;
    if (ordnance_count == 0xff) {
      uVar7 = 100;
      uVar4 = 100;
    }
    if ((DAT_00027e7a == uVar4) && (DAT_00027e7c == uVar7)) {
      *(ushort *)(&DAT_00027e8a + sVar1) = (ushort)ordnance_count;
    }
    else {
      DAT_00027e7c = DAT_00027e7c + 1;
      if (0x50 < DAT_00027e7c) {
        DAT_00027e7c = 1;
      }
      if (((DAT_00027e7a != uVar4) && (DAT_00027e7c < 9)) &&
         (DAT_00027e7a = DAT_00027e7a + 1, 0x50 < DAT_00027e7a)) {
        DAT_00027e7a = 1;
      }
    }
    clip_top = 0x13;
    clip_bottom = 0x1c;
    (*_draw_shape_automask)();
    (*_draw_shape_automask)();
  }
  bVar5 = lives;
  if ((char)lives < '\0') {
    bVar5 = 0;
  }
  uVar7 = (ushort)bVar5;
  if (9 < bVar5) {
    uVar7 = 9;
  }
  if (uVar7 != *(ushort *)(&DAT_00027e8c + sVar1)) {
    sVar6 = uVar7 * -8 + 0x59;
    if (sVar6 == DAT_00027e7e) {
      *(ushort *)(&DAT_00027e8c + sVar1) = uVar7;
    }
    else if (sVar6 < DAT_00027e7e) {
      DAT_00027e7e = DAT_00027e7e + -1;
    }
    else {
      DAT_00027e7e = DAT_00027e7e + 1;
    }
    clip_top = 0x13;
    clip_bottom = 0x1c;
    (*_draw_shape_automask)();
  }
  if (score != *(int *)(&DAT_00027e90 + sVar1)) {
    *(int *)(&DAT_00027e90 + sVar1) = score;
    draw_score();
  }
  uVar7 = (ushort)enemy_planes_destroyed;
  if (99 < uVar7) {
    uVar7 = 99;
  }
  if (uVar7 != *(ushort *)(&DAT_00027e8e + sVar1)) {
    *(ushort *)(&DAT_00027e8e + sVar1) = uVar7;
    clip_top = 0x14;
    clip_bottom = 0x1c;
    blit_digit();
    blit_digit();
    clip_top = 0x13;
    clip_bottom = 0x1f;
    hud_draw_kill_tally();
    hud_draw_kill_tally();
  }
  (*_wait_disown_blitter)();
  return 0;
}


// ==== hud_draw_kill_tally @ 0001f200 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void hud_draw_kill_tally(void)

{
  short unaff_D2w;
  
  for (; 0 < unaff_D2w; unaff_D2w = unaff_D2w + -1) {
    (*_draw_shape_automask)();
  }
  return;
}


// ==== draw_enemy_warning_light @ 0001f21a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_enemy_warning_light(void)

{
  short sVar1;
  short *psVar2;
  
  psVar2 = &enemy_planes;
  sVar1 = 3;
  while ((*psVar2 == 0 || ((psVar2[1] & 7U) != 4))) {
    psVar2 = psVar2 + 0x1a;
    sVar1 = sVar1 + -1;
    if (sVar1 == -1) {
      return;
    }
  }
  (*_draw_shape_automask)();
  return;
}


// ==== draw_score @ 0001f26a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 draw_score(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  char *pcVar1;
  
  clip_top = 0xb;
  clip_bottom = 0x12;
  (*_format_string)();
  pcVar1 = &DAT_00027e72;
  while (*pcVar1 != '\0') {
    blit_digit();
    pcVar1 = pcVar1 + 1;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== blit_digit @ 0001f2b0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 blit_digit(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_blit_shape)();
  return CONCAT44(in_D0,in_D1);
}


// ==== clip_dashboard @ 0001f2dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void clip_dashboard(void)

{
  (*_set_clip_rect)();
  return;
}


// ==== FUN_0001f2ec @ 0001f2ec ====

byte * FUN_0001f2ec(byte *param_1)

{
  byte *pbVar1;
  byte local_f [11];
  
  pbVar1 = local_f;
  for (; (*param_1 != 0 && (*param_1 != 0x20)); param_1 = param_1 + 1) {
    *pbVar1 = (byte)DAT_0002683e ^ *param_1 & 0x5f;
    pbVar1 = pbVar1 + 1;
  }
  *pbVar1 = 0;
  return local_f;
}


// ==== FUN_0001f332 @ 0001f332 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001f332(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_36 [50];
  
  (*_thunk_FUN_00022e78)(back_playfield_rastport,(int)param_1._0_2_,(int)param_1._2_2_);
  (*_thunk_FUN_000215d8)(auStack_36,param_2,&stack0x0000000c);
  FUN_00018570(auStack_36);
  return;
}


// ==== FUN_0001f374 @ 0001f374 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001f374(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*_thunk_FUN_00022ea4)(back_playfield_rastport,(int)param_3._0_2_);
  (*_thunk_FUN_00022e78)(back_playfield_rastport,(int)param_1._0_2_,(int)param_1._2_2_);
  (*_thunk_FUN_00022e48)(back_playfield_rastport,(int)param_2._0_2_,(int)param_1._2_2_);
  (*_thunk_FUN_00022e48)(back_playfield_rastport,(int)param_2._0_2_,(int)param_2._2_2_);
  (*_thunk_FUN_00022e48)(back_playfield_rastport,(int)param_1._0_2_,(int)param_2._2_2_);
  (*_thunk_FUN_00022e48)(back_playfield_rastport,(int)param_1._0_2_,(int)param_1._2_2_);
  return;
}


// ==== FUN_0001f41a @ 0001f41a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_0001f41a(void)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  undefined1 auStack_90 [50];
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  short local_58;
  undefined2 local_56;
  undefined4 local_54;
  undefined1 auStack_50 [65];
  undefined1 local_f [11];
  
  local_56 = 0;
  (*_thunk_FUN_00021eca)(0x6840,(short)auStack_50);
  (*_thunk_FUN_00016b60)();
  local_54 = back_playfield_rastport;
  (*_thunk_FUN_00021246)((short)back_playfield_rastport);
  (*_set_clip_full_bitmap)();
  (*_thunk_FUN_000203be)();
  (*_thunk_FUN_000203be)();
  (*_thunk_FUN_000203be)();
  (*_thunk_FUN_000203be)();
  uVar2 = (*_thunk_FUN_000203be)();
  uVar2 = uVar2 & 0xff;
  while (uVar2 != 0) {
    (*_thunk_FUN_000203be)();
    uVar2 = uVar2 - 1;
  }
  local_58 = (*_thunk_FUN_00015d5a)();
  iVar1 = (local_58 % 0x21) * 0x10;
  FUN_0001f374(0x2b,0xa4);
  (*_thunk_FUN_00022ea4)((short)local_54,1);
  local_5a = *(undefined2 *)(&DAT_0002661e + iVar1);
  local_5c = *(undefined2 *)(&DAT_00026620 + iVar1);
  local_5e = *(undefined2 *)(&DAT_00026622 + iVar1);
  FUN_0001f332(0x30,0xf658);
  FUN_0001f332(0x3d,0xf677);
  FUN_0001f332(0x4a,0xf696);
  FUN_0001f332(0x57,0xf6a7);
  FUN_0001f332(100,0xf6c6);
  FUN_0001f332(0x71,0xf6e5);
  FUN_0001f332(0x82,0xf6f2);
  (*_thunk_FUN_00022ea4)((short)local_54,2);
  (*_thunk_FUN_00022e78)((short)back_playfield_rastport,0x70,0x8c);
  (*_thunk_FUN_000215d8)((short)auStack_90,0xf70d,local_5c);
  FUN_00018570((short)auStack_90);
  (*_thunk_FUN_00022ea4)((short)local_54);
  (*_flip_views_and_wait)((short)back_view);
  (*_thunk_FUN_00017084)((short)auStack_50);
  local_f[0] = 0;
  (*_thunk_FUN_00022ea4)((short)local_54,5);
  FUN_0001f374(0x91,0x99);
  (*_text_input_field)((short)local_f,200,0);
  sVar3 = (*_thunk_FUN_00021e9a)((short)local_f,0xf727);
  if (sVar3 == 0) {
    local_56 = 1;
  }
  uVar4 = FUN_0001f2ec((short)local_f,(short)(iVar1 + 0x26624));
  sVar3 = (*_thunk_FUN_00021e9a)(uVar4);
  if (sVar3 == 0) {
    local_56 = 1;
  }
  (*_thunk_FUN_000173b0)();
  return local_56;
}


// ==== FUN_0001f79c @ 0001f79c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0001f79c(ushort param_1,ushort param_2,short param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = (*_thunk_FUN_00020848)(0x2c,param_4,param_5);
  iVar3 = DAT_00026e72;
  (**(code **)(DAT_00026e72 + -0xcc))();
  *(ushort *)(iVar1 + 0x1a) = param_2;
  *(ushort *)(iVar1 + 0x18) = param_1;
  uVar2 = (**(code **)(iVar3 + -0x23a))();
  *(undefined4 *)(iVar1 + 4) = uVar2;
  uVar2 = (*_thunk_FUN_00020848)(100);
  *(undefined4 *)(iVar1 + 0x28) = uVar2;
  (**(code **)(DAT_00026e72 + -0xc6))();
  uVar2 = (*_thunk_FUN_00020848)(0xc);
  *(undefined4 *)(iVar1 + 0x24) = uVar2;
  uVar2 = (*_thunk_FUN_00020848)(0x28);
  *(undefined4 *)(*(int *)(iVar1 + 0x24) + 4) = uVar2;
  *(undefined4 *)(*(int *)(iVar1 + 0x28) + 4) = uVar2;
  (**(code **)(DAT_00026e72 + -0x186))();
  piVar4 = (int *)(*(int *)(*(int *)(iVar1 + 0x24) + 4) + 8);
  do {
    param_3 = param_3 + -1;
    if (param_3 == -1) {
      *(short *)(iVar1 + 0x1c) = (short)param_4;
      *(short *)(iVar1 + 0x1e) = (short)param_5;
      return iVar1;
    }
    iVar3 = (*_thunk_FUN_0002085e)((uint)(param_1 >> 3) * (uint)param_2);
    *piVar4 = iVar3;
    piVar4 = piVar4 + 1;
  } while (iVar3 != 0);
  FUN_0001f8a2();
  return 0;
}


// ==== FUN_0001f89e @ 0001f89e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001f89e(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  ushort uVar3;
  undefined4 *puVar4;
  
  (**(code **)(DAT_00026e72 + -0x21c))();
  iVar2 = *(int *)(*(int *)(param_1 + 0x24) + 4);
  if (iVar2 != 0) {
    uVar3 = (ushort)*(byte *)(iVar2 + 5);
    puVar4 = (undefined4 *)(iVar2 + 8);
    while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
      uVar1 = *puVar4;
      puVar4 = puVar4 + 1;
      (*_thunk_FUN_0002090a)(uVar1);
    }
    (*_thunk_FUN_0002090a)(*(undefined4 *)(*(int *)(param_1 + 0x24) + 4));
  }
  (*_thunk_FUN_0002090a)(*(undefined4 *)(param_1 + 0x24));
  (*_thunk_FUN_0002090a)(*(undefined4 *)(param_1 + 0x28));
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(DAT_00026e72 + -0x240))();
  }
  (*_thunk_FUN_0002090a)(param_1);
  return 0;
}


// ==== FUN_0001f8a2 @ 0001f8a2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001f8a2(void)

{
  undefined4 uVar1;
  int iVar2;
  ushort uVar3;
  int in_A0;
  undefined4 *puVar4;
  
  (**(code **)(DAT_00026e72 + -0x21c))();
  iVar2 = *(int *)(*(int *)(in_A0 + 0x24) + 4);
  if (iVar2 != 0) {
    uVar3 = (ushort)*(byte *)(iVar2 + 5);
    puVar4 = (undefined4 *)(iVar2 + 8);
    while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
      uVar1 = *puVar4;
      puVar4 = puVar4 + 1;
      (*_thunk_FUN_0002090a)(uVar1);
    }
    (*_thunk_FUN_0002090a)(*(undefined4 *)(*(int *)(in_A0 + 0x24) + 4));
  }
  (*_thunk_FUN_0002090a)(*(undefined4 *)(in_A0 + 0x24));
  (*_thunk_FUN_0002090a)(*(undefined4 *)(in_A0 + 0x28));
  if (*(int *)(in_A0 + 4) != 0) {
    (**(code **)(DAT_00026e72 + -0x240))();
  }
  (*_thunk_FUN_0002090a)();
  return 0;
}


// ==== FUN_0001f946 @ 0001f946 ====

undefined4 FUN_0001f946(void)

{
  byte bVar1;
  bool bVar2;
  short in_D0w;
  ushort uVar3;
  ushort uVar4;
  undefined4 in_D1;
  ushort uVar5;
  ushort uVar6;
  ushort unaff_D2w;
  short sVar7;
  ushort uVar8;
  short sVar9;
  short sVar10;
  char unaff_D6b;
  byte *in_A0;
  byte *pbVar11;
  int *in_A1;
  int *piVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  
  sVar10 = (short)in_D1 + -1;
  uVar3 = ((ushort)(in_D0w + 0xfU) >> 4) << 1;
  iVar15 = 0;
  do {
    iVar13 = *in_A1;
    pbVar11 = in_A0;
    piVar12 = in_A1 + 1;
    iVar14 = iVar15;
    uVar4 = uVar3;
    sVar9 = (unaff_D2w & 0xff) - 1;
LAB_0001f97e:
    do {
      sVar7 = 0;
      bVar1 = *pbVar11;
      uVar5 = (ushort)bVar1;
      in_A0 = pbVar11;
      uVar6 = uVar3;
      uVar8 = uVar3;
      if (unaff_D6b == '\0') {
        while (uVar5 = uVar6 - 1, uVar5 != 0xffff) {
LAB_0001f99c:
          *(byte *)(iVar13 + iVar14) = *in_A0;
          iVar14 = iVar14 + 1;
          in_A0 = in_A0 + 1;
          uVar6 = uVar5;
        }
LAB_0001f9c2:
        sVar7 = uVar8 + 1;
      }
      else {
        in_A0 = pbVar11 + 1;
        if (-1 < (char)bVar1) {
          uVar8 = (ushort)bVar1;
          goto LAB_0001f99c;
        }
        if (bVar1 != 0x80) {
          uVar6 = (ushort)(byte)-bVar1;
          uVar8 = (ushort)(byte)-bVar1;
          do {
            *(byte *)(iVar13 + iVar14) = *in_A0;
            iVar14 = iVar14 + 1;
            uVar6 = uVar6 - 1;
          } while (uVar6 != 0xffff);
          in_A0 = pbVar11 + 2;
          goto LAB_0001f9c2;
        }
      }
      uVar6 = uVar4 - sVar7;
      bVar2 = sVar7 <= (short)uVar4;
      pbVar11 = in_A0;
      uVar4 = uVar6;
    } while (uVar6 != 0 && bVar2);
    sVar9 = sVar9 + -1;
    if (sVar9 != -1) {
      iVar13 = *piVar12;
      piVar12 = piVar12 + 1;
      iVar14 = iVar15;
      uVar4 = uVar3;
      goto LAB_0001f97e;
    }
    sVar10 = sVar10 + -1;
    iVar15 = iVar14;
    if (sVar10 == -1) {
      return in_D1;
    }
  } while( true );
}


// ==== FUN_0001f9dc @ 0001f9dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 * FUN_0001f9dc(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  int *piVar8;
  undefined1 *puVar9;
  int *in_A1;
  undefined1 *puVar10;
  bool bVar11;
  undefined8 uVar12;
  ushort uVar7;
  
  bVar11 = false;
  (**(code **)(DAT_00026e6e + -0x54))();
  if (!bVar11) {
    iVar2 = (*_thunk_FUN_00020848)(0x104);
    iVar5 = DAT_00026e6e;
    if (iVar2 == 0) {
      (**(code **)(DAT_00026e6e + -0x5a))();
    }
    else {
      (**(code **)(DAT_00026e6e + -0x66))();
      (**(code **)(iVar5 + -0x5a))();
      uVar1 = *(undefined4 *)(iVar2 + 0x7c);
      (*_thunk_FUN_0002090a)(iVar2);
      iVar5 = DAT_00026e6e;
      iVar3 = (**(code **)(DAT_00026e6e + -0x1e))();
      if (iVar3 != 0) {
        uVar12 = (*_thunk_FUN_00020848)(uVar1);
        iVar3 = DAT_00026e6e;
        puVar4 = (undefined1 *)((ulonglong)uVar12 >> 0x20);
        if (puVar4 == (undefined1 *)0x0) {
          (**(code **)(_DAT_00000004 + -0x20a))(0,(int)uVar12,0x3ed,iVar2);
          (**(code **)(iVar5 + -0x24))();
        }
        else {
          iVar5 = (**(code **)(DAT_00026e6e + -0x2a))();
          if (iVar5 == 0) {
            (**(code **)(iVar3 + -0x24))();
          }
          else {
            (**(code **)(iVar3 + -0x24))();
            if (in_A1 == (int *)0x0) {
              return puVar4;
            }
            iVar5 = *(int *)(puVar4 + 0x10);
            iVar2 = iVar5 + 0x14;
            for (piVar8 = (int *)(iVar5 + 4 + (int)(puVar4 + 0x10)); *piVar8 != 0x424f4459;
                piVar8 = (int *)(piVar8[1] + 8 + (int)piVar8)) {
              iVar2 = piVar8[1] + 8 + iVar2;
            }
            uVar6 = iVar2 + 4;
            uVar12 = (*_thunk_FUN_00020848)(uVar6);
            iVar5 = (int)((ulonglong)uVar12 >> 0x20);
            *in_A1 = iVar5;
            if (iVar5 != 0) {
              FUN_0001f946();
              puVar9 = puVar4;
              puVar10 = (undefined1 *)*in_A1;
              while (uVar7 = (short)uVar6 - 1, uVar6 = (uint)uVar7, uVar7 != 0xffff) {
                *puVar10 = *puVar9;
                puVar9 = puVar9 + 1;
                puVar10 = puVar10 + 1;
              }
              (*_thunk_FUN_0002090a)(puVar4);
              (*_thunk_FUN_0002090a)(*in_A1);
              return (undefined1 *)0x0;
            }
            (**(code **)(_DAT_00000004 + -0x20a))(0,(int)uVar12,puVar4,piVar8 + 2);
          }
        }
      }
    }
  }
  return (undefined1 *)0xffffffff;
}


// ==== FUN_0001fc2a @ 0001fc2a ====

/* WARNING: Removing unreachable block (ram,0x0001fce0) */
/* WARNING: Removing unreachable block (ram,0x0001fd06) */
/* WARNING: Removing unreachable block (ram,0x0001fd02) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001fc2a(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_00026e6e;
  iVar1 = (**(code **)(DAT_00026e6e + -0x1e))();
  if (iVar1 != 0) {
    iVar3 = 0;
    iVar1 = (**(code **)(iVar2 + -0x2a))();
    iVar2 = DAT_00026e6e;
    if ((0 < iVar1) && (iVar3 == 0x464f524d)) {
      (**(code **)(DAT_00026e6e + -0x42))();
      iVar2 = (**(code **)(iVar2 + -0x2a))();
      if (iVar2 == 0) {
        return 0;
      }
      do {
        iVar2 = DAT_00026e6e;
        (**(code **)(DAT_00026e6e + -0x42))();
        iVar2 = (**(code **)(iVar2 + -0x2a))();
      } while (iVar2 != 0);
    }
    (**(code **)(DAT_00026e6e + -0x24))();
  }
  return 0;
}


// ==== FUN_0001fd2e @ 0001fd2e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001fd2e(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = FUN_0001fc2a();
  if (iVar1 != 0) {
    for (iVar2 = *(int *)(iVar1 + 0x10) + iVar1 + 0x10; piVar3 = (int *)(iVar2 + 4),
        *piVar3 != 0x434d4150; iVar2 = *(int *)(iVar2 + 8) + (int)piVar3) {
      if (*piVar3 == 0x424f4459) {
        return;
      }
    }
    FUN_0001fdb4();
    (*_thunk_FUN_0002090a)(iVar1);
  }
  return;
}


// ==== FUN_0001fdb4 @ 0001fdb4 ====

void FUN_0001fdb4(void)

{
  byte bVar1;
  bool bVar2;
  short sVar3;
  short in_D0w;
  byte *in_A0;
  byte *pbVar4;
  byte *pbVar5;
  ushort *in_A1;
  
  do {
    pbVar4 = in_A0 + 1;
    bVar1 = *in_A0;
    pbVar5 = in_A0 + 2;
    in_A0 = in_A0 + 3;
    *in_A1 = (ushort)(*pbVar5 >> 4) | (ushort)*pbVar4 | (ushort)bVar1 << 4;
    sVar3 = in_D0w + -3;
    bVar2 = 2 < in_D0w;
    in_D0w = sVar3;
    in_A1 = in_A1 + 1;
  } while (sVar3 != 0 && bVar2);
  return;
}


// ==== FUN_0001fdd6 @ 0001fdd6 ====

undefined4 FUN_0001fdd6(int param_1,int param_2)

{
  undefined4 in_D0;
  short sVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  
  sVar1 = *(short *)(param_1 + 2);
  puVar2 = *(undefined2 **)(param_1 + 4);
  puVar3 = *(undefined2 **)(param_2 + 4);
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return in_D0;
}


// ==== FUN_0001fdfe @ 0001fdfe ====

undefined8 FUN_0001fdfe(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (**(code **)(DAT_00026e72 + -0x1e))();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001fe36 @ 0001fe36 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001fe36(undefined4 param_1,undefined4 param_2)

{
  (*_thunk_FUN_0002090a)(param_1,param_2);
  (*_thunk_FUN_0002090a)();
  return;
}


// ==== FUN_0001fe50 @ 0001fe50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_0001fe50(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined2 local_6;
  
  local_6 = 0;
  iVar1 = (*_thunk_FUN_00022b30)(param_1,0x3ee);
  if (iVar1 == 0) {
    local_6 = (*_thunk_FUN_00022b06)();
  }
  else {
    iVar2 = (*_thunk_FUN_00021d6e)(iVar1,param_2,param_3);
    (*_thunk_FUN_00022ab2)(iVar1);
    if (iVar2 != param_3) {
      local_6 = (*_thunk_FUN_00022b06)();
    }
  }
  return local_6;
}


// ==== FUN_0001feb4 @ 0001feb4 ====

void FUN_0001feb4(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10001);
  return;
}


// ==== FUN_0001feca @ 0001feca ====

void FUN_0001feca(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10003);
  return;
}


// ==== FUN_0001fee0 @ 0001fee0 ====

void FUN_0001fee0(byte *param_1,int param_2,byte *param_3)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar6 = param_1 + param_2;
  while (param_1 < pbVar6) {
    pbVar4 = param_1 + 1;
    bVar1 = *param_1;
    uVar2 = (ushort)bVar1;
    if ((char)bVar1 < '\0') {
      sVar3 = (byte)-bVar1 - 1;
      pbVar5 = param_3;
      do {
        param_1 = pbVar4 + 1;
        param_3 = pbVar5 + 1;
        *pbVar5 = *pbVar4;
        sVar3 = sVar3 + -1;
        pbVar4 = param_1;
        pbVar5 = param_3;
      } while (sVar3 != -1);
    }
    else {
      param_1 = param_1 + 2;
      bVar1 = *pbVar4;
      pbVar4 = param_3;
      do {
        param_3 = pbVar4 + 1;
        *pbVar4 = bVar1;
        uVar2 = uVar2 - 1;
        pbVar4 = param_3;
      } while (uVar2 != 0xffff);
    }
  }
  return;
}


// ==== FUN_0001ff16 @ 0001ff16 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0001ff16(undefined4 param_1,undefined4 param_2)

{
  short sVar3;
  int iVar1;
  undefined4 *puVar2;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24 [4];
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_28 = 0;
  local_2c = 0;
  local_30 = 0;
  local_34 = 0;
  DAT_00027eb2 = 0;
  local_8 = (*_thunk_FUN_00022b1e)(param_1,0xfffffffe);
  if (local_8 != 0) {
    local_28 = (*_thunk_FUN_00020848)(0x104);
    if (local_28 == 0) {
      DAT_00027eb2 = 1000000;
    }
    else {
      sVar3 = (*_thunk_FUN_00022ade)(local_8,local_28);
      if (sVar3 != 0) {
        (*_thunk_FUN_00022b54)(local_8);
        local_8 = 0;
        local_14 = *(int *)(local_28 + 0x7c);
        (*_thunk_FUN_0002090a)(local_28);
        local_28 = 0;
        if (0 < local_14) {
          if (local_14 < 0x10) {
            iVar1 = FUN_00020390(param_1,param_2);
            return iVar1;
          }
          local_2c = (*_thunk_FUN_00022b30)(param_1,0x3ed);
          if (((local_2c != 0) &&
              (local_c = (*_thunk_FUN_00022b42)(local_2c,local_24,0x10), local_c == 0x10)) &&
             (local_24[0] != 0x50636b64)) {
            if (local_24[0] == 0x5270636b) {
              local_10 = local_24[1];
              local_30 = FUN_00020874(local_24[1],param_2);
              if (local_30 == 0) {
                DAT_00027eb2 = 1000000;
              }
              else {
                puVar2 = (undefined4 *)(*_thunk_FUN_00020848)(local_14 + -8);
                if (puVar2 == (undefined4 *)0x0) {
                  DAT_00027eb2 = 1000000;
                  local_34 = 0;
                }
                else {
                  local_c = (*_thunk_FUN_00022b42)(local_2c,puVar2 + 2,local_14 + -0x10);
                  (*_thunk_FUN_00022ab2)(local_2c);
                  local_2c = 0;
                  if (local_14 + -0x10 == local_c) {
                    *puVar2 = local_24[2];
                    puVar2[1] = local_24[3];
                    FUN_0001fee0(puVar2,local_14 + -8,local_30,local_10);
                    (*_thunk_FUN_0002090a)(puVar2);
                    DAT_0002767a = local_10;
                    DAT_00027bca = local_30;
                    return local_30;
                  }
                  local_34 = 0;
                }
              }
            }
            else {
              local_34 = FUN_00020874(local_14,param_2);
              if (local_34 == 0) {
                DAT_00027eb2 = 1000000;
              }
              else {
                sVar3 = 0;
                do {
                  *(int *)(local_34 + sVar3 * 4) = local_24[sVar3];
                  sVar3 = sVar3 + 1;
                } while (sVar3 < 4);
                local_c = (*_thunk_FUN_00022b42)(local_2c,local_34 + 0x10,local_14 + -0x10);
                (*_thunk_FUN_00022ab2)(local_2c);
                local_2c = 0;
                if (local_14 + -0x10 == local_c) {
                  DAT_0002767a = local_14;
                  DAT_00027bca = local_34;
                  return local_34;
                }
              }
            }
          }
        }
      }
    }
  }
  if (DAT_00027eb2 == 0) {
    DAT_00027eb2 = (*_thunk_FUN_00022b06)();
  }
  if (local_34 != 0) {
    (*_thunk_FUN_0002090a)(local_34);
  }
  if (local_30 != 0) {
    (*_thunk_FUN_0002090a)(local_30);
  }
  if (local_2c != 0) {
    (*_thunk_FUN_00022ab2)(local_2c);
  }
  if (local_28 != 0) {
    (*_thunk_FUN_0002090a)(local_28);
  }
  if (local_8 != 0) {
    (*_thunk_FUN_00022b54)(local_8);
  }
  DAT_00027bca = 0;
  DAT_0002767a = 0;
  return 0;
}


// ==== FUN_00020220 @ 00020220 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00020220(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  short sVar4;
  int iVar3;
  int local_c;
  int local_8;
  
  local_8 = 0;
  DAT_00027bca = 0;
  bVar2 = true;
  DAT_00027eb2 = 0;
  local_c = thunk_FUN_00022d3a(0x104,0);
  if (local_c == 0) {
    DAT_00027eb2 = 1000000;
  }
  else {
    local_8 = (*_thunk_FUN_00022b1e)(param_1,0xfffffffe);
    if ((local_8 != 0) && (sVar4 = (*_thunk_FUN_00022ade)(local_8,local_c), sVar4 != 0)) {
      (*_thunk_FUN_00022b54)(local_8);
      local_8 = 0;
      iVar1 = *(int *)(local_c + 0x7c);
      thunk_FUN_00022d8a(local_c,0x104);
      local_c = 0;
      if (param_2 == 0) {
        DAT_00027bca = FUN_00020874(iVar1,param_3);
        if (DAT_00027bca == 0) {
          DAT_00027eb2 = 1000000;
          goto LAB_0002031e;
        }
      }
      else {
        DAT_00027bca = param_2;
      }
      iVar3 = (*_thunk_FUN_00022b30)(param_1,0x3ed);
      if (iVar3 != 0) {
        DAT_0002767a = (*_thunk_FUN_00022b42)(iVar3,DAT_00027bca,iVar1);
        (*_thunk_FUN_00022ab2)(iVar3);
        if (DAT_0002767a == iVar1) {
          bVar2 = false;
        }
      }
    }
  }
LAB_0002031e:
  if (bVar2) {
    if (DAT_00027eb2 == 0) {
      DAT_00027eb2 = (*_thunk_FUN_00022b06)();
    }
    if (param_2 == 0) {
      (*_thunk_FUN_0002090a)(DAT_00027bca);
    }
    DAT_00027bca = 0;
    DAT_0002767a = 0;
  }
  if (local_8 != 0) {
    (*_thunk_FUN_00022b54)(local_8);
  }
  if (local_c != 0) {
    thunk_FUN_00022d8a(local_c,0x104);
  }
  return DAT_00027bca;
}


// ==== FUN_00020390 @ 00020390 ====

void FUN_00020390(undefined4 param_1,undefined4 param_2)

{
  FUN_00020220(param_1,0,param_2);
  return;
}


// ==== FUN_000203be @ 000203be ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000203be(void)

{
  DAT_00026860 = _DAT_00dff006 ^ DAT_00026862 * 0x1afb - 0x333U;
  return;
}


// ==== FUN_000203da @ 000203da ====

void FUN_000203da(undefined4 param_1)

{
  DAT_00026860 = param_1._0_2_;
  DAT_00026862 = param_1._0_2_;
  return;
}


// ==== FUN_000203e8 @ 000203e8 ====

void FUN_000203e8(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  byte bVar1;
  ushort uVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar6 = (byte *)*param_2;
  pbVar3 = (byte *)*param_1;
  do {
    while( true ) {
      pbVar4 = pbVar3 + 1;
      bVar1 = *pbVar3;
      uVar2 = (ushort)bVar1;
      if (-1 < (char)bVar1) break;
      pbVar5 = pbVar4;
      if (bVar1 != 0x80) {
        uVar2 = (ushort)(byte)-bVar1;
        param_3._0_2_ = (param_3._0_2_ - uVar2) + -1;
        pbVar5 = pbVar3 + 2;
        bVar1 = *pbVar4;
        pbVar3 = pbVar6;
        do {
          pbVar6 = pbVar3 + 1;
          *pbVar3 = bVar1;
          uVar2 = uVar2 - 1;
          pbVar3 = pbVar6;
        } while (uVar2 != 0xffff);
      }
      pbVar3 = pbVar5;
      if (param_3._0_2_ < 1) goto LAB_0002042a;
    }
    param_3._0_2_ = (param_3._0_2_ - uVar2) + -1;
    pbVar3 = pbVar6;
    do {
      pbVar5 = pbVar4 + 1;
      pbVar6 = pbVar3 + 1;
      *pbVar3 = *pbVar4;
      uVar2 = uVar2 - 1;
      pbVar4 = pbVar5;
      pbVar3 = pbVar6;
    } while (uVar2 != 0xffff);
    pbVar3 = pbVar5;
  } while (0 < param_3._0_2_);
LAB_0002042a:
  *param_1 = pbVar5;
  *param_2 = pbVar6;
  return;
}


// ==== FUN_0002044c @ 0002044c ====

void FUN_0002044c(void)

{
  DAT_00027eb6 = read_fire_button();
  return;
}


// ==== FUN_00020454 @ 00020454 ====

void FUN_00020454(void)

{
  DAT_00027692 = FUN_00020488();
  return;
}


// ==== read_fire_button @ 0002046a ====

undefined4 read_fire_button(void)

{
  if ((DAT_00bfe0ff & 0x40) == 0) {
    return 1;
  }
  if ((DAT_00bfe001 & 0x80) == 0) {
    return 1;
  }
  return 0;
}


// ==== FUN_00020488 @ 00020488 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_00020488(void)

{
  undefined4 in_D1;
  
  return (ulonglong)
         CONCAT14((&LAB_000204b0)[(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3)],in_D1);
}


// ==== FUN_000204e4 @ 000204e4 ====

void FUN_000204e4(void)

{
  return;
}


// ==== FUN_000204ec @ 000204ec ====

void FUN_000204ec(void)

{
  return;
}


// ==== FUN_000204f4 @ 000204f4 ====

undefined4 FUN_000204f4(void)

{
  undefined4 extraout_A0;
  
  find_shape_by_name();
  return extraout_A0;
}


// ==== FUN_0002050e @ 0002050e ====

int FUN_0002050e(int param_1,undefined4 param_2)

{
  return param_1 + (uint)(ushort)(*(short *)(param_1 + 4) << 3) +
                   *(int *)(param_1 + (uint)(ushort)(param_2._0_2_ + *(short *)(param_1 + 4)) * 4 +
                           6) + 6;
}


// ==== find_shape_by_name @ 00020560 ====

undefined8 find_shape_by_name(void)

{
  int *piVar1;
  int in_D0;
  int iVar2;
  undefined4 in_D1;
  short sVar3;
  int in_A0;
  int *piVar4;
  
  sVar3 = *(short *)(in_A0 + 4);
  if (0 < sVar3) {
    piVar1 = (int *)(in_A0 + 6);
    do {
      piVar4 = piVar1;
      if (in_D0 <= *piVar4) break;
      sVar3 = sVar3 + -1;
      piVar1 = piVar4 + 1;
    } while (sVar3 != -1);
    if (in_D0 == *piVar4) {
      iVar2 = *(short *)(in_A0 + 4) * 8 +
              in_A0 + *(int *)((short)((uint)((int)piVar4 + (-6 - in_A0)) >> 2) * 4 +
                               *(short *)(in_A0 + 4) * 4 + in_A0 + 6) + 6;
      goto LAB_000205ac;
    }
  }
  iVar2 = 0;
LAB_000205ac:
  return CONCAT44(iVar2,in_D1);
}


// ==== FUN_000205cc @ 000205cc ====

void FUN_000205cc(undefined4 param_1)

{
  DAT_00026c80 = param_1._0_2_;
  DAT_00026c08 = 10;
  DAT_00026c06 = 0;
  DAT_00026c0a = FUN_00022ba4(0,0);
  DAT_00026c12 = FUN_00022c8e(DAT_00026c0a);
  DAT_00026c24 = &DAT_00026c2c;
  DAT_00026c28 = FUN_0002075a;
  DAT_00026c1f = 0x7f;
  FUN_00022dc4(s_input_device_00026866,0,DAT_00026c12,0);
  *(undefined2 *)(DAT_00026c12 + 0x1c) = 9;
  *(undefined **)(DAT_00026c12 + 0x28) = &DAT_00026c16;
  FUN_00022d50(DAT_00026c12);
  DAT_00026c0e = FUN_00022ba4(0,0);
  DAT_00026c7c = FUN_00022cb6(DAT_00026c0e,0x20);
  FUN_00022dc4(s_console_device_00026873,0xffffffff,DAT_00026c7c,0);
  DAT_00027eba = *(undefined4 *)(DAT_00026c7c + 0x14);
  return;
}


// ==== FUN_0002067c @ 0002067c ====

void FUN_0002067c(void)

{
  if (DAT_00026c7c != 0) {
    FUN_00022b88(DAT_00026c7c);
    FUN_00022cfa(DAT_00026c7c);
    DAT_00026c7c = 0;
    FUN_00022c30(DAT_00026c0e);
    DAT_00026c0e = 0;
    *(undefined2 *)(DAT_00026c12 + 0x1c) = 10;
    *(undefined **)(DAT_00026c12 + 0x28) = &DAT_00026c16;
    FUN_00022d50(DAT_00026c12);
    FUN_00022b88(DAT_00026c12);
    FUN_00022ca4(DAT_00026c12);
    DAT_00026c12 = 0;
    FUN_00022c30(DAT_00026c0a);
    DAT_00026c0a = 0;
  }
  return;
}


// ==== FUN_000206ee @ 000206ee ====

void FUN_000206ee(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_000207e4();
  FUN_00020700(uVar1);
  return;
}


// ==== FUN_00020700 @ 00020700 ====

ushort FUN_00020700(undefined4 param_1)

{
  short sVar1;
  byte local_20 [2];
  undefined4 local_1e;
  undefined1 local_1a;
  undefined1 local_19;
  undefined2 local_18;
  undefined2 local_16;
  ushort local_6;
  
  local_6 = 0;
  local_1e = 0;
  local_1a = 1;
  local_19 = 0;
  local_18 = param_1._2_2_;
  local_16 = (undefined2)((uint)param_1 >> 0x10);
  sVar1 = FUN_00022f30(&local_1e,local_20,1,0);
  if (sVar1 == 1) {
    local_6 = (ushort)local_20[0];
  }
  return local_6;
}


// ==== FUN_0002075a @ 0002075a ====

void FUN_0002075a(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int *in_A0;
  
  do {
    sVar3 = DAT_00026c06;
    uVar1 = *(ushort *)((int)in_A0 + 6);
    uVar2 = *(ushort *)(in_A0 + 2);
    if (*(char *)(in_A0 + 1) == '\x02') {
      if (uVar1 == 0x69) {
        DAT_00027ebe = CONCAT11(0xff,(undefined1)DAT_00027ebe);
      }
      if (uVar1 == 0xe9) {
        DAT_00027ebe = 0;
        goto LAB_0002078c;
      }
    }
    else {
LAB_0002078c:
      if (((*(char *)(in_A0 + 1) == '\x01') && ((uVar1 & 0x80) == 0)) &&
         ((DAT_00026c80 == 0 || ((DAT_00026c80 & uVar2) != 0)))) {
        if (DAT_00026c06 < DAT_00026c08) {
          (&DAT_00026be8)[DAT_00026c06] = (char)uVar1;
          *(ushort *)((int)&DAT_00026bf2 + (int)(short)(sVar3 * 2)) = uVar2;
          DAT_00026c06 = DAT_00026c06 + 1;
        }
        *(undefined2 *)(in_A0 + 1) = 0;
      }
    }
    in_A0 = (int *)*in_A0;
    if (in_A0 == (int *)0x0) {
      return;
    }
  } while( true );
}


// ==== FUN_000207d8 @ 000207d8 ====

undefined4 FUN_000207d8(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (DAT_00026c06 != 0) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// ==== FUN_000207e4 @ 000207e4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000207e4(void)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 in_D1;
  short sVar4;
  short sVar5;
  undefined1 in_ZF;
  
  while( true ) {
    FUN_000207d8();
    if (!(bool)in_ZF) break;
    (*_thunk_FUN_00022eee)();
  }
  (*_thunk_FUN_00022d48)();
  uVar2 = DAT_00026bf2;
  bVar1 = DAT_00026be8;
  uVar3 = CONCAT31((int3)(((uint)DAT_00026bf2 << 0x10) >> 8),DAT_00026be8);
  DAT_00026c06 = DAT_00026c06 + -1;
  sVar4 = 0;
  sVar5 = 0;
  do {
    (&DAT_00026be8)[sVar4] = (&DAT_00026be9)[sVar4];
    *(undefined2 *)((int)&DAT_00026bf2 + (int)sVar5) =
         *(undefined2 *)((int)&DAT_00026bf4 + (int)sVar5);
    sVar4 = sVar4 + 1;
    sVar5 = sVar5 + 2;
  } while (sVar4 <= DAT_00026c06);
  (*_thunk_FUN_00022d66)();
  if (DAT_00026c80 != 0) {
    uVar3 = (uint)(~DAT_00026c80 & uVar2) << 0x10 | (uint)bVar1;
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== FUN_00020848 @ 00020848 ====

void FUN_00020848(undefined4 param_1)

{
  FUN_00020874(param_1,0x10001);
  return;
}


// ==== FUN_0002085e @ 0002085e ====

void FUN_0002085e(undefined4 param_1)

{
  FUN_00020874(param_1,0x10003);
  return;
}


// ==== FUN_00020874 @ 00020874 ====

int * FUN_00020874(int param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = (int *)thunk_FUN_00022d3a(param_1 + 0xc,param_2 | 0x10000);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    *piVar1 = param_1 + 0xc;
    if (DAT_00026882 == (int *)0x0) {
      DAT_00026882 = piVar1;
      piVar1[1] = (int)piVar1;
      piVar1[2] = (int)piVar1;
    }
    else {
      piVar1[1] = (int)DAT_00026882;
      piVar1[2] = DAT_00026882[2];
      *(int **)(DAT_00026882[2] + 4) = piVar1;
      DAT_00026882[2] = (int)piVar1;
    }
    piVar1 = piVar1 + 3;
  }
  return piVar1;
}


// ==== FUN_0002090a @ 0002090a ====

undefined4 FUN_0002090a(int param_1)

{
  undefined4 *puVar1;
  
  if (param_1 != 0) {
    if (param_1 == -1) {
      while (DAT_00026882 != (undefined4 *)0x0) {
        FUN_0002090a(DAT_00026882 + 3);
      }
    }
    else {
      puVar1 = (undefined4 *)(param_1 + -0xc);
      if (puVar1 == DAT_00026882) {
        DAT_00026882 = *(undefined4 **)(param_1 + -8);
      }
      if (puVar1 == *(undefined4 **)(param_1 + -8)) {
        DAT_00026882 = (undefined4 *)0x0;
      }
      *(undefined4 *)(*(int *)(param_1 + -8) + 8) = *(undefined4 *)(param_1 + -4);
      *(undefined4 *)(*(int *)(param_1 + -4) + 4) = *(undefined4 *)(param_1 + -8);
      thunk_FUN_00022d8a(puVar1,*puVar1);
    }
  }
  return 0;
}


// ==== blit_clip_setup @ 000209bc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void blit_clip_setup(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  ushort in_D0w;
  short in_D1w;
  ushort uVar4;
  ushort uVar5;
  ushort *in_A0;
  int in_A1;
  bool bVar6;
  
  if (in_A0 == (ushort *)0x0) {
    return;
  }
  DAT_00027ee8 = *in_A0 * in_A0[1];
  DAT_00027ed6 = in_A0 + 10;
  uVar4 = in_A0[1];
  DAT_00027eda = in_A1;
  if (in_D1w < clip_top) {
    sVar1 = in_D1w - clip_top;
    bVar6 = SCARRY2(sVar1,uVar4);
    uVar4 = sVar1 + uVar4;
    if (uVar4 == 0 || bVar6 != (int)((uint)uVar4 << 0x10) < 0) {
      return;
    }
    DAT_00027ed6 = (ushort *)((uint)(ushort)-sVar1 * (uint)*in_A0 + (int)DAT_00027ed6);
    DAT_00027eda = (uint)(ushort)-sVar1 * (uint)*in_A0 + in_A1;
    in_D1w = clip_top;
  }
  uVar5 = (uVar4 + in_D1w) - clip_bottom;
  if ((uVar5 != 0 && SBORROW2(uVar4 + in_D1w,clip_bottom) == (int)((uint)uVar5 << 0x10) < 0) &&
     (bVar6 = SBORROW2(uVar4,uVar5), uVar4 = uVar4 - uVar5,
     uVar4 == 0 || bVar6 != (int)((uint)uVar4 << 0x10) < 0)) {
    return;
  }
  DAT_00027ef0 = 0xffff;
  uVar5 = *in_A0;
  DAT_00027eee = in_D0w & 0xf;
  if (DAT_00027eee == 0) {
    DAT_00027ef2 = 0xffff;
    _DAT_00027ee4 = 0;
  }
  else {
    uVar5 = uVar5 + 2;
    DAT_00027ef2 = 0;
    _DAT_00027ee4 = 0xfffefffe;
  }
  if ((short)in_D0w < (short)clip_left) {
    sVar1 = (short)((in_D0w - clip_left) + 0xf) >> 4;
    sVar3 = sVar1 * 2;
    if (sVar3 != 0) {
      bVar6 = SCARRY2(sVar3,uVar5);
      uVar5 = sVar3 + uVar5;
      if (uVar5 == 0 || bVar6 != (int)((uint)uVar5 << 0x10) < 0) {
        DAT_00027ef0 = 0xffff;
        return;
      }
      _DAT_00027ee4 = CONCAT22(DAT_00027ee4 + sVar1 * -2,DAT_00027ee6 + sVar1 * -2);
      DAT_00027ed6 = (ushort *)((int)DAT_00027ed6 - (int)sVar3);
      DAT_00027eda = DAT_00027eda - sVar3;
    }
    DAT_00027ef0 = *(undefined2 *)(&DAT_000268b8 + (short)((-(in_D0w - clip_left) & 0xf) * 2));
    in_D0w = clip_left;
    if (DAT_00027eee != 0) {
      in_D0w = clip_left - 0x10;
    }
  }
  sVar1 = (in_D0w & 0xfff0) + uVar5 * 8;
  if (SCARRY2(in_D0w & 0xfff0,uVar5 * 8)) {
    return;
  }
  uVar2 = sVar1 - clip_right;
  if (uVar2 != 0 && SBORROW2(sVar1,clip_right) == (int)((uint)uVar2 << 0x10) < 0) {
    sVar1 = (short)uVar2 >> 3;
    bVar6 = SBORROW2(uVar5,sVar1);
    uVar5 = uVar5 - sVar1;
    if (uVar5 == 0 || bVar6 != (int)((uint)uVar5 << 0x10) < 0) {
      return;
    }
    _DAT_00027ee4 = CONCAT22(sVar1 + DAT_00027ee4,sVar1 + DAT_00027ee6);
    DAT_00027ef2 = *(undefined2 *)(&DAT_000268da + (short)((0x10 - DAT_00027eee) * 2));
  }
  DAT_00027ee2 = *current_bitmap - uVar5;
  DAT_00027ee0 = uVar5 >> 1 | uVar4 << 6;
  DAT_00027ede = in_D1w * *current_bitmap + ((short)in_D0w >> 4) * 2;
  if (in_A1 == 0) {
    DAT_00027eda = 0;
  }
  return;
}


// ==== FUN_00020aee @ 00020aee ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020aee(void)

{
  (*_own_blitter)();
  blit_shape();
                    /* WARNING: Could not recover jumptable at 0x00020b08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_wait_disown_blitter)();
  return;
}


// ==== blit_shape @ 00020b0c ====

undefined8 blit_shape(void)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  short sVar5;
  undefined2 uVar6;
  short sVar7;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar8;
  ushort uVar9;
  byte bVar10;
  int in_A0;
  int iVar11;
  int *piVar12;
  byte *pbVar13;
  int unaff_A6;
  undefined1 in_CF;
  
  blit_clip_setup();
  sVar7 = DAT_00027ee8;
  uVar6 = DAT_00027ee0;
  sVar5 = DAT_00027ede;
  iVar4 = DAT_00027eda;
  iVar11 = DAT_00027ed6;
  if (!(bool)in_CF) {
    bVar2 = *(byte *)(current_rastport + 0x18);
    uVar8 = DAT_00027eee << 0xc | DAT_00027eee >> 4;
    bVar10 = *(byte *)(unaff_A6 + 2);
    while ((bVar10 & 0x40) != 0) {
      bVar10 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = DAT_00027ef0;
    *(undefined2 *)(unaff_A6 + 0x46) = DAT_00027ef2;
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    uVar9 = 0xbca;
    if (iVar4 == 0) {
      uVar9 = 0x3ca;
      *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
      if (uVar8 == 0) {
        uVar9 = 0x1ca;
        *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
      }
    }
    uVar9 = uVar9 | uVar8;
    *(undefined2 *)(unaff_A6 + 100) = DAT_00027ee6;
    *(undefined2 *)(unaff_A6 + 0x62) = DAT_00027ee4;
    *(undefined2 *)(unaff_A6 + 0x60) = DAT_00027ee2;
    *(undefined2 *)(unaff_A6 + 0x66) = DAT_00027ee2;
    bVar10 = bVar2 & *(byte *)(in_A0 + 0xc);
    if (bVar10 != 0) {
      piVar12 = (int *)(current_bitmap + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0;
      do {
        bVar3 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar3 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar4;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    bVar10 = bVar2 & *(byte *)(in_A0 + 0xd);
    if (bVar10 != 0) {
      piVar12 = (int *)(current_bitmap + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar3 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar3 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar4;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar8;
    *(ushort *)(unaff_A6 + 0x40) = uVar9 | 0x400;
    pbVar13 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar13 == 0) break;
      bVar10 = bVar2 & *pbVar13;
      if (bVar10 != 0) {
        piVar12 = (int *)(current_bitmap + 8);
        do {
          bVar3 = bVar10 & 1;
          bVar10 = bVar10 >> 1;
          if (bVar3 != 0) {
            iVar1 = *piVar12;
            *(int *)(unaff_A6 + 0x50) = iVar4;
            *(int *)(unaff_A6 + 0x4c) = iVar11;
            *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
            bVar3 = *(byte *)(unaff_A6 + 2);
            while ((bVar3 & 0x40) != 0) {
              bVar3 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar12 = piVar12 + 1;
        } while (bVar10 != 0);
      }
      iVar11 = sVar7 + iVar11;
      pbVar13 = pbVar13 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00020ca8 @ 00020ca8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020ca8(undefined4 param_1)

{
  mask_buffer_size = param_1;
  mask_buffer = (*_thunk_FUN_0002085e)(param_1);
  if (mask_buffer == 0) {
    mask_buffer_size = 0;
  }
  return;
}


// ==== FUN_00020cc4 @ 00020cc4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020cc4(void)

{
  (*_own_blitter)();
  draw_shape_automask();
                    /* WARNING: Could not recover jumptable at 0x00020cde. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_wait_disown_blitter)();
  return;
}


// ==== draw_shape_automask @ 00020ce2 ====

undefined4 draw_shape_automask(void)

{
  int iVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  undefined2 uVar6;
  short sVar7;
  undefined4 in_D0;
  uint uVar8;
  undefined4 uVar9;
  ushort uVar10;
  ushort uVar11;
  short sVar12;
  byte bVar13;
  int iVar14;
  ushort *in_A0;
  uint *puVar15;
  int in_A1;
  ushort *puVar16;
  uint *puVar17;
  uint *puVar18;
  uint *puVar19;
  uint *puVar20;
  uint *puVar21;
  int *piVar22;
  int unaff_A6;
  bool bVar23;
  
  bVar23 = false;
  if (in_A1 != 0) {
    blit_clip_setup();
    sVar12 = DAT_00027ee8;
    uVar6 = DAT_00027ee0;
    sVar7 = DAT_00027ede;
    iVar5 = DAT_00027eda;
    iVar14 = DAT_00027ed6;
    if (!bVar23) {
      bVar3 = *(byte *)(current_rastport + 0x18);
      uVar10 = DAT_00027eee << 0xc | DAT_00027eee >> 4;
      bVar13 = *(byte *)(unaff_A6 + 2);
      while ((bVar13 & 0x40) != 0) {
        bVar13 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) = DAT_00027ef0;
      *(undefined2 *)(unaff_A6 + 0x46) = DAT_00027ef2;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar11 = 0xbca;
      if (iVar5 == 0) {
        uVar11 = 0x3ca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        if (uVar10 == 0) {
          uVar11 = 0x1ca;
          *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
        }
      }
      uVar11 = uVar11 | uVar10;
      *(undefined2 *)(unaff_A6 + 100) = DAT_00027ee6;
      *(undefined2 *)(unaff_A6 + 0x62) = DAT_00027ee4;
      *(undefined2 *)(unaff_A6 + 0x60) = DAT_00027ee2;
      *(undefined2 *)(unaff_A6 + 0x66) = DAT_00027ee2;
      bVar13 = bVar3 & *(byte *)(in_A0 + 6);
      if (bVar13 != 0) {
        piVar22 = (int *)(current_bitmap + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0;
        do {
          bVar4 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar4 != 0) {
            iVar1 = *piVar22;
            *(int *)(unaff_A6 + 0x50) = iVar5;
            *(int *)(unaff_A6 + 0x48) = sVar7 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar7 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
            bVar4 = *(byte *)(unaff_A6 + 2);
            while ((bVar4 & 0x40) != 0) {
              bVar4 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar22 = piVar22 + 1;
        } while (bVar13 != 0);
      }
      bVar13 = bVar3 & *(byte *)((int)in_A0 + 0xd);
      if (bVar13 != 0) {
        piVar22 = (int *)(current_bitmap + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        do {
          bVar4 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar4 != 0) {
            iVar1 = *piVar22;
            *(int *)(unaff_A6 + 0x50) = iVar5;
            *(int *)(unaff_A6 + 0x48) = sVar7 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar7 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
            bVar4 = *(byte *)(unaff_A6 + 2);
            while ((bVar4 & 0x40) != 0) {
              bVar4 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar22 = piVar22 + 1;
        } while (bVar13 != 0);
      }
      *(ushort *)(unaff_A6 + 0x42) = uVar10;
      *(ushort *)(unaff_A6 + 0x40) = uVar11 | 0x400;
      puVar16 = in_A0 + 7;
      while( true ) {
        if (*(byte *)puVar16 == 0) break;
        bVar13 = bVar3 & *(byte *)puVar16;
        if (bVar13 != 0) {
          piVar22 = (int *)(current_bitmap + 8);
          do {
            bVar4 = bVar13 & 1;
            bVar13 = bVar13 >> 1;
            if (bVar4 != 0) {
              iVar1 = *piVar22;
              *(int *)(unaff_A6 + 0x50) = iVar5;
              *(int *)(unaff_A6 + 0x4c) = iVar14;
              *(int *)(unaff_A6 + 0x48) = sVar7 + iVar1;
              *(int *)(unaff_A6 + 0x54) = sVar7 + iVar1;
              *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
              bVar4 = *(byte *)(unaff_A6 + 2);
              while ((bVar4 & 0x40) != 0) {
                bVar4 = *(byte *)(unaff_A6 + 2);
              }
            }
            piVar22 = piVar22 + 1;
          } while (bVar13 != 0);
        }
        iVar14 = sVar12 + iVar14;
        puVar16 = (ushort *)((int)puVar16 + 1);
      }
    }
    return in_D0;
  }
  uVar8 = (uint)*in_A0 * (uint)in_A0[1];
  if (mask_buffer_size <= uVar8 && uVar8 - mask_buffer_size != 0) {
    uVar9 = blit_shape();
    return uVar9;
  }
  puVar16 = in_A0 + 7;
  sVar7 = -1;
  do {
    sVar12 = sVar7;
    cVar2 = *(char *)puVar16;
    puVar16 = (ushort *)((int)puVar16 + 1);
    sVar7 = sVar12 + 1;
  } while (cVar2 != '\0');
  if ((short)(sVar12 + 1) != 0 && sVar12 != 0) {
    puVar15 = (uint *)(in_A0 + 10);
    uVar11 = (ushort)uVar8;
    puVar21 = (uint *)((int)puVar15 + (int)(short)uVar11);
    puVar17 = (uint *)((int)puVar21 + (int)(short)uVar11);
    puVar18 = (uint *)((int)puVar17 + (int)(short)uVar11);
    puVar19 = (uint *)((int)puVar18 + (int)(short)uVar11);
    uVar10 = uVar11 >> 1;
    if (sVar12 == 1) {
      uVar11 = uVar11 >> 2;
      puVar17 = mask_buffer;
      if ((uVar10 & 1) != 0) {
        puVar17 = (uint *)((int)mask_buffer + 2);
        *(ushort *)mask_buffer = *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar21 = puVar21 + 1;
      }
    }
    else if (sVar12 == 2) {
      uVar11 = uVar11 >> 2;
      puVar18 = mask_buffer;
      if ((uVar10 & 1) != 0) {
        puVar18 = (uint *)((int)mask_buffer + 2);
        *(ushort *)mask_buffer = *(ushort *)puVar17 | *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar17 = (uint *)((int)puVar17 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar18 = *puVar17 | *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar18 = puVar18 + 1;
        puVar21 = puVar21 + 1;
        puVar17 = puVar17 + 1;
      }
    }
    else if (sVar12 == 3) {
      uVar11 = uVar11 >> 2;
      puVar19 = mask_buffer;
      if ((uVar10 & 1) != 0) {
        puVar19 = (uint *)((int)mask_buffer + 2);
        *(ushort *)mask_buffer =
             *(ushort *)puVar18 | *(ushort *)puVar17 | *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar19 = *puVar18 | *puVar17 | *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar19 = puVar19 + 1;
        puVar21 = puVar21 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
      }
    }
    else {
      uVar11 = uVar11 >> 2;
      puVar20 = mask_buffer;
      if ((uVar10 & 1) != 0) {
        puVar20 = (uint *)((int)mask_buffer + 2);
        *(ushort *)mask_buffer =
             *(ushort *)puVar19 |
             *(ushort *)puVar18 | *(ushort *)puVar17 | *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar19 = (uint *)((int)puVar19 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar20 = *puVar19 | *puVar18 | *puVar17 | *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar20 = puVar20 + 1;
        puVar21 = puVar21 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar19 = puVar19 + 1;
      }
    }
  }
  uVar9 = blit_shape();
  return uVar9;
}


// ==== FUN_00020e0a @ 00020e0a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020e0a(void)

{
  (*_own_blitter)();
  blit_shape_xor();
                    /* WARNING: Could not recover jumptable at 0x00020e20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_wait_disown_blitter)();
  return;
}


// ==== blit_shape_xor @ 00020e24 ====

undefined8 blit_shape_xor(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  short sVar6;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar7;
  byte bVar8;
  int in_A0;
  int iVar9;
  int iVar10;
  int *piVar11;
  byte *pbVar12;
  int unaff_A6;
  undefined1 in_CF;
  
  blit_clip_setup();
  sVar5 = DAT_00027ee8;
  uVar4 = DAT_00027ee0;
  sVar3 = DAT_00027ede;
  iVar9 = DAT_00027ed6;
  if (!(bool)in_CF) {
    bVar1 = *(byte *)(current_rastport + 0x18);
    uVar7 = DAT_00027eee << 0xc | DAT_00027eee >> 4;
    bVar8 = *(byte *)(unaff_A6 + 2);
    while ((bVar8 & 0x40) != 0) {
      bVar8 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = DAT_00027ef0;
    sVar6 = DAT_00027ef4;
    *(short *)(unaff_A6 + 0x46) = DAT_00027ef4;
    if (sVar6 == 0) {
      *(undefined2 *)(unaff_A6 + 0x46) = DAT_00027ef2;
    }
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
    *(undefined2 *)(unaff_A6 + 0x62) = DAT_00027ee4;
    *(undefined2 *)(unaff_A6 + 0x60) = DAT_00027ee2;
    *(undefined2 *)(unaff_A6 + 0x66) = DAT_00027ee2;
    *(int *)(unaff_A6 + 0x4c) = iVar9;
    bVar8 = bVar1 & *(byte *)(in_A0 + 0xd);
    if (bVar8 != 0) {
      piVar11 = (int *)(current_bitmap + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x36a;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar2 = bVar8 & 1;
        bVar8 = bVar8 >> 1;
        if (bVar2 != 0) {
          iVar10 = (int)sVar3 + *piVar11;
          *(int *)(unaff_A6 + 0x48) = iVar10;
          *(int *)(unaff_A6 + 0x54) = iVar10;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
          bVar2 = *(byte *)(unaff_A6 + 2);
          while ((bVar2 & 0x40) != 0) {
            bVar2 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar11 = piVar11 + 1;
      } while (bVar8 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar7;
    *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x76a;
    pbVar12 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar12 == 0) break;
      bVar8 = bVar1 & *pbVar12;
      if (bVar8 != 0) {
        piVar11 = (int *)(current_bitmap + 8);
        do {
          bVar2 = bVar8 & 1;
          bVar8 = bVar8 >> 1;
          if (bVar2 != 0) {
            iVar10 = (int)sVar3 + *piVar11;
            *(int *)(unaff_A6 + 0x4c) = iVar9;
            *(int *)(unaff_A6 + 0x48) = iVar10;
            *(int *)(unaff_A6 + 0x54) = iVar10;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar2 = *(byte *)(unaff_A6 + 2);
            while ((bVar2 & 0x40) != 0) {
              bVar2 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar11 = piVar11 + 1;
        } while (bVar8 != 0);
      }
      iVar9 = sVar5 + iVar9;
      pbVar12 = pbVar12 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00020f54 @ 00020f54 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020f54(void)

{
  (*_own_blitter)();
  FUN_00020f7c();
  (*_wait_disown_blitter)();
  return;
}


// ==== FUN_00020f7c @ 00020f7c ====

void FUN_00020f7c(void)

{
  byte bVar1;
  ushort in_D0w;
  short in_D1w;
  int in_A0;
  undefined4 in_A1;
  int unaff_A2;
  int unaff_A6;
  
  bVar1 = *(byte *)(unaff_A6 + 2);
  while ((bVar1 & 0x40) != 0) {
    bVar1 = *(byte *)(unaff_A6 + 2);
  }
  *(undefined2 *)(unaff_A6 + 0x44) = 0xffff;
  *(undefined2 *)(unaff_A6 + 0x46) = 0xffff;
  *(undefined2 *)(unaff_A6 + 100) = 0;
  *(undefined2 *)(unaff_A6 + 0x62) = 0;
  *(undefined2 *)(unaff_A6 + 0x60) = 0;
  *(undefined2 *)(unaff_A6 + 0x66) = 0;
  *(int *)(unaff_A6 + 0x50) = unaff_A2;
  *(int *)(unaff_A6 + 0x4c) = in_A0;
  *(undefined4 *)(unaff_A6 + 0x48) = in_A1;
  *(undefined4 *)(unaff_A6 + 0x54) = in_A1;
  *(undefined2 *)(unaff_A6 + 0x42) = 0;
  *(undefined2 *)(unaff_A6 + 0x40) = 0xfca;
  if ((in_A0 == 0) && (*(undefined2 *)(unaff_A6 + 0x40) = 0xb0a, unaff_A2 == 0)) {
    return;
  }
  if (unaff_A2 == 0) {
    *(undefined2 *)(unaff_A6 + 0x40) = 0x5cc;
  }
  *(ushort *)(unaff_A6 + 0x58) = in_D1w << 6 | in_D0w >> 1;
  return;
}


// ==== FUN_00020ff2 @ 00020ff2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020ff2(void)

{
  (*_own_blitter)();
  fill_rect();
  (*_wait_disown_blitter)();
  return;
}


// ==== fill_rect @ 00021010 ====

undefined8 fill_rect(void)

{
  short sVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short *psVar6;
  uint in_D0;
  uint uVar7;
  ushort uVar8;
  uint in_D1;
  uint uVar9;
  short sVar10;
  ushort unaff_D2w;
  undefined2 uVar11;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar12;
  ushort uVar13;
  undefined3 uVar14;
  undefined4 unaff_D7;
  int iVar15;
  int *piVar16;
  int *piVar17;
  int unaff_A6;
  
  psVar6 = current_bitmap;
  uVar7 = in_D0;
  if ((short)in_D0 < (short)clip_left) {
    uVar7 = (uint)clip_left;
  }
  if (clip_right <= (short)unaff_D2w) {
    unaff_D2w = clip_right - 1;
  }
  uVar9 = in_D1;
  if ((short)in_D1 < (short)clip_top) {
    uVar9 = (uint)clip_top;
  }
  if (clip_bottom <= unaff_D3w) {
    unaff_D3w = clip_bottom + -1;
  }
  uVar8 = (ushort)uVar7;
  sVar10 = (short)uVar9;
  uVar14 = (undefined3)((uint)unaff_D7 >> 8);
  if (((uVar8 | unaff_D2w + 1) & 0xf) != 0) {
    sVar3 = (unaff_D3w - sVar10) + 1;
    if (sVar3 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
      sVar1 = *current_bitmap;
      uVar13 = (short)uVar8 >> 3 & 0xfffe;
      sVar4 = ((short)unaff_D2w >> 3 & 0xfffeU) + 2;
      bVar2 = *(byte *)(unaff_A6 + 2);
      while ((bVar2 & 0x40) != 0) {
        bVar2 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(&DAT_000268b8 + (short)((uVar8 & 0xf) * 2))
      ;
      *(undefined2 *)(unaff_A6 + 0x46) =
           *(undefined2 *)(&DAT_000268dc + (short)((unaff_D2w & 0xf) * 2));
      uVar8 = sVar4 - uVar13;
      if (uVar8 != 0 && (short)uVar13 <= sVar4) {
        sVar4 = *psVar6;
        *(ushort *)(unaff_A6 + 0x62) = sVar4 - uVar8;
        *(ushort *)(unaff_A6 + 0x66) = sVar4 - uVar8;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x42) = 0;
        uVar12 = (ushort)*(byte *)((int)psVar6 + 5);
        uVar7 = CONCAT31(uVar14,*(undefined1 *)(current_rastport + 0x18));
        piVar17 = (int *)(psVar6 + 4);
        while (uVar12 = uVar12 - 1, uVar12 != 0xffff) {
          piVar16 = piVar17 + 1;
          iVar15 = *piVar17;
          uVar11 = 0x50c;
          uVar9 = unaff_D4 & 1;
          unaff_D4 = unaff_D4 >> 1 & 0x7fff;
          if (uVar9 != 0) {
            uVar11 = 0x5fc;
          }
          uVar9 = uVar7 & 1;
          uVar7 = uVar7 >> 1 & 0x7fff;
          piVar17 = piVar16;
          if (uVar9 != 0) {
            iVar15 = (short)(uVar13 + sVar10 * sVar1) + iVar15;
            bVar2 = *(byte *)(unaff_A6 + 2);
            while ((bVar2 & 0x40) != 0) {
              bVar2 = *(byte *)(unaff_A6 + 2);
            }
            *(int *)(unaff_A6 + 0x4c) = iVar15;
            *(int *)(unaff_A6 + 0x54) = iVar15;
            *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
            *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar3 * 0x40;
          }
        }
      }
    }
    return CONCAT44(in_D0,in_D1);
  }
  sVar3 = (unaff_D3w - sVar10) + 1;
  if (sVar3 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
    sVar1 = *current_bitmap;
    sVar4 = (short)(uVar8 + 0xf & 0xfff0) >> 3;
    sVar5 = (short)(unaff_D2w + 1 & 0xfff0) >> 3;
    bVar2 = *(byte *)(unaff_A6 + 2);
    while ((bVar2 & 0x40) != 0) {
      bVar2 = *(byte *)(unaff_A6 + 2);
    }
    uVar8 = sVar5 - sVar4;
    if (uVar8 != 0 && sVar4 <= sVar5) {
      *(ushort *)(unaff_A6 + 0x66) = *current_bitmap - uVar8;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar6 + 5);
      uVar7 = CONCAT31(uVar14,*(undefined1 *)(current_rastport + 0x18));
      piVar17 = (int *)(psVar6 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar16 = piVar17 + 1;
        iVar15 = *piVar17;
        uVar11 = 0x100;
        uVar9 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar9 != 0) {
          uVar11 = 0x1ff;
        }
        uVar9 = uVar7 & 1;
        uVar7 = uVar7 >> 1 & 0x7fff;
        piVar17 = piVar16;
        if (uVar9 != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
          while ((bVar2 & 0x40) != 0) {
            bVar2 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar4 + sVar10 * sVar1) + iVar15;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
          *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar3 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00021120 @ 00021120 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00021120(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_own_blitter)();
  fill_rect_aligned();
  (*_wait_disown_blitter)();
  return CONCAT44(in_D0,in_D1);
}


// ==== fill_rect_aligned @ 0002113e ====

undefined8 fill_rect_aligned(void)

{
  int iVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  short *psVar9;
  uint in_D0;
  uint uVar10;
  uint in_D1;
  uint uVar11;
  short unaff_D2w;
  undefined2 uVar12;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar13;
  undefined4 unaff_D7;
  int *piVar14;
  int *piVar15;
  int unaff_A6;
  
  psVar9 = current_bitmap;
  uVar10 = in_D0;
  if ((short)in_D0 < (short)clip_left) {
    uVar10 = (uint)clip_left;
  }
  if (clip_right <= unaff_D2w) {
    unaff_D2w = clip_right + -1;
  }
  uVar11 = in_D1;
  if ((short)in_D1 < (short)clip_top) {
    uVar11 = (uint)clip_top;
  }
  if (clip_bottom <= unaff_D3w) {
    unaff_D3w = clip_bottom + -1;
  }
  sVar4 = unaff_D3w - (short)uVar11;
  sVar3 = sVar4 + 1;
  if (sVar3 != 0 && -2 < sVar4) {
    sVar4 = *current_bitmap;
    sVar6 = (short)((short)uVar10 + 0xfU & 0xfff0) >> 3;
    sVar7 = (short)(unaff_D2w + 1U & 0xfff0) >> 3;
    bVar2 = *(byte *)(unaff_A6 + 2);
    while ((bVar2 & 0x40) != 0) {
      bVar2 = *(byte *)(unaff_A6 + 2);
    }
    uVar5 = sVar7 - sVar6;
    if (uVar5 != 0 && sVar6 <= sVar7) {
      *(ushort *)(unaff_A6 + 0x66) = *current_bitmap - uVar5;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar9 + 5);
      uVar10 = CONCAT31((int3)((uint)unaff_D7 >> 8),*(undefined1 *)(current_rastport + 0x18));
      piVar15 = (int *)(psVar9 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar14 = piVar15 + 1;
        iVar1 = *piVar15;
        uVar12 = 0x100;
        uVar8 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar8 != 0) {
          uVar12 = 0x1ff;
        }
        uVar8 = uVar10 & 1;
        uVar10 = uVar10 >> 1 & 0x7fff;
        piVar15 = piVar14;
        if (uVar8 != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
          while ((bVar2 & 0x40) != 0) {
            bVar2 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar6 + (short)uVar11 * sVar4) + iVar1;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar12;
          *(ushort *)(unaff_A6 + 0x58) = uVar5 >> 1 | sVar3 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00021246 @ 00021246 ====

undefined4 FUN_00021246(int param_1)

{
  int iVar1;
  undefined4 in_D0;
  ushort uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  current_rastport = param_1;
  iVar1 = *(int *)(param_1 + 4);
  current_bitmap = iVar1;
  *(byte *)(param_1 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = &DAT_0002688c;
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== set_rastport @ 0002124a ====

undefined4 set_rastport(void)

{
  int iVar1;
  undefined4 in_D0;
  ushort uVar2;
  int in_A0;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = *(int *)(in_A0 + 4);
  current_rastport = in_A0;
  current_bitmap = iVar1;
  *(byte *)(in_A0 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = &DAT_0002688c;
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== set_clip_full_bitmap @ 00021280 ====

undefined8 set_clip_full_bitmap(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  set_clip_rect();
  return CONCAT44(in_D0,in_D1);
}


// ==== set_clip_rect @ 0002129c ====

void set_clip_rect(void)

{
  undefined2 in_D0w;
  short in_D1w;
  ushort unaff_D2w;
  ushort unaff_D3w;
  
  clip_top = in_D0w;
  clip_bottom = in_D1w;
  clip_left = unaff_D2w & 0xfff0;
  clip_right = unaff_D3w & 0xfff0;
  DAT_000268b6 = (unaff_D3w & 0xfff0) - 1;
  DAT_000268b4 = in_D1w + -1;
  return;
}


// ==== own_blitter @ 000212ce ====

void own_blitter(void)

{
  FUN_00022e8a();
  return;
}


// ==== wait_disown_blitter @ 000212d4 ====

void wait_disown_blitter(void)

{
  do {
  } while ((DAT_00dff002 & 0x40) != 0);
  FUN_00022e40();
  return;
}


// ==== FUN_000212fa @ 000212fa ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000212fa(void)

{
  (*_own_blitter)();
  draw_line_clipped();
  (*_wait_disown_blitter)();
  return;
}


// ==== draw_line_clipped @ 00021318 ====

undefined8 draw_line_clipped(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  ushort *puVar7;
  uint in_D0;
  uint uVar8;
  uint in_D1;
  uint uVar9;
  ushort unaff_D2w;
  ushort uVar10;
  ushort unaff_D3w;
  uint unaff_D4;
  ushort uVar12;
  int iVar11;
  ushort uVar13;
  ushort uVar14;
  uint uVar15;
  ushort *puVar16;
  ushort *puVar17;
  int iVar18;
  int unaff_A6;
  undefined4 local_34;
  
  puVar7 = current_bitmap;
  DAT_000268b4 = clip_bottom - 1;
  DAT_000268b6 = clip_right - 1;
  uVar15 = unaff_D4 & 0xffff;
  uVar12 = 10;
  if (((short)clip_left <= (short)unaff_D2w) && (uVar12 = 2, (short)DAT_000268b6 < (short)unaff_D2w)
     ) {
    uVar12 = 6;
  }
  if (((short)clip_top <= (short)unaff_D3w) &&
     (uVar12 = uVar12 & 0xfffd, (short)DAT_000268b4 < (short)unaff_D3w)) {
    uVar12 = uVar12 | 1;
  }
  uVar14 = 10;
  if (((short)clip_left <= (short)in_D0) && (uVar14 = 2, (short)DAT_000268b6 < (short)in_D0)) {
    uVar14 = 6;
  }
  if (((short)clip_top <= (short)in_D1) &&
     (uVar14 = uVar14 & 0xfffd, (short)DAT_000268b4 < (short)in_D1)) {
    uVar14 = uVar14 | 1;
  }
  local_34 = CONCAT22(uVar14,uVar12);
  uVar8 = in_D0;
  uVar9 = in_D1;
  while( true ) {
    uVar12 = (ushort)uVar8;
    uVar14 = (ushort)uVar9;
    if (local_34._2_2_ == 0 && local_34._0_2_ == 0) {
      DAT_00027efc = CONCAT11(DAT_00027efc._0_1_,*(undefined1 *)(current_rastport + 0x18));
      iVar11 = (uint)*current_bitmap * (uVar9 & 0xffff);
      uVar13 = unaff_D3w - uVar14;
      if ((short)uVar13 < 0) {
        uVar13 = -uVar13;
      }
      uVar5 = unaff_D2w - uVar12;
      if ((short)uVar5 < 0) {
        uVar5 = -uVar5;
      }
      uVar10 = uVar5;
      uVar6 = uVar13;
      if ((short)uVar13 < (short)uVar5) {
        uVar10 = uVar13;
        uVar6 = uVar5;
      }
      bVar1 = (&DAT_000268fc)
              [(short)(ushort)(byte)(((unaff_D3w < uVar14) * '\x02' + (unaff_D2w < uVar12)) * '\x02'
                                    + (uVar13 < uVar5))];
      sVar3 = uVar10 * 2;
      uVar14 = (ushort)*(byte *)((int)current_bitmap + 5);
      puVar17 = current_bitmap + 4;
      while (uVar14 = uVar14 - 1, uVar14 != 0xffff) {
        bVar2 = *(byte *)(unaff_A6 + 2);
        while ((bVar2 & 0x40) != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
        }
        puVar16 = puVar17 + 2;
        iVar18 = *(int *)puVar17;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x44) = 0xffff;
        *(ushort *)(unaff_A6 + 0x40) = uVar12 << 0xc | 0xbca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0x8000;
        uVar8 = uVar15 & 1;
        uVar15 = uVar15 >> 1;
        if (uVar8 == 0) {
          *(undefined2 *)(unaff_A6 + 0x72) = 0;
        }
        uVar13 = DAT_00027efc & 1;
        DAT_00027efc = DAT_00027efc >> 1;
        puVar17 = puVar16;
        if (uVar13 != 0) {
          *(short *)(unaff_A6 + 0x62) = sVar3;
          uVar13 = (ushort)bVar1;
          if (sVar3 < (short)uVar6) {
            uVar13 = bVar1 | 0x40;
          }
          *(ushort *)(unaff_A6 + 0x52) = sVar3 - uVar6;
          *(ushort *)(unaff_A6 + 100) = (sVar3 - uVar6) - uVar6;
          *(ushort *)(unaff_A6 + 0x42) = uVar13;
          iVar18 = CONCAT22((short)((uint)iVar11 >> 0x10),(uVar12 >> 4) * 2 + (short)iVar11) +
                   iVar18;
          *(int *)(unaff_A6 + 0x48) = iVar18;
          *(int *)(unaff_A6 + 0x54) = iVar18;
          *(ushort *)(unaff_A6 + 0x60) = *puVar7;
          *(ushort *)(unaff_A6 + 0x66) = *puVar7;
          *(ushort *)(unaff_A6 + 0x58) = (uVar6 + 1) * 0x40 + 2;
        }
      }
      return CONCAT44(in_D0,in_D1);
    }
    if ((local_34._2_2_ & local_34._0_2_) != 0) break;
    sVar3 = unaff_D2w - uVar12;
    sVar4 = unaff_D3w - uVar14;
    if (local_34._0_2_ == 0) {
      uVar12 = unaff_D3w;
      if ((local_34 & 8) == 0) {
        if ((local_34 & 4) == 0) {
          uVar14 = unaff_D2w;
          if ((local_34 & 2) == 0) {
            if (((local_34 & 1) != 0) && (uVar12 = DAT_000268b4, sVar3 != 0)) {
              uVar14 = (short)(((int)(short)(DAT_000268b4 - unaff_D3w) * (int)sVar3) / (int)sVar4) +
                       unaff_D2w;
              uVar12 = DAT_000268b4;
            }
          }
          else {
            uVar12 = clip_top;
            if (sVar3 != 0) {
              uVar14 = (short)(((int)(short)(clip_top - unaff_D3w) * (int)sVar3) / (int)sVar4) +
                       unaff_D2w;
              uVar12 = clip_top;
            }
          }
        }
        else {
          uVar14 = DAT_000268b6;
          if (sVar4 != 0) {
            uVar14 = DAT_000268b6;
            uVar12 = (short)(((int)(short)(DAT_000268b6 - unaff_D2w) * (int)sVar4) / (int)sVar3) +
                     unaff_D3w;
          }
        }
      }
      else {
        uVar14 = clip_left;
        if (sVar4 != 0) {
          uVar14 = clip_left;
          uVar12 = (short)(((int)(short)(clip_left - unaff_D2w) * (int)sVar4) / (int)sVar3) +
                   unaff_D3w;
        }
      }
      unaff_D3w = uVar12;
      unaff_D2w = uVar14;
      uVar12 = 10;
      if (((short)clip_left <= (short)unaff_D2w) &&
         (uVar12 = 2, (short)DAT_000268b6 < (short)unaff_D2w)) {
        uVar12 = 6;
      }
      if (((short)clip_top <= (short)unaff_D3w) &&
         (uVar12 = uVar12 & 0xfffd, (short)DAT_000268b4 < (short)unaff_D3w)) {
        uVar12 = uVar12 | 1;
      }
      local_34 = (uint)uVar12;
    }
    else {
      if ((local_34 & 0x80000) == 0) {
        if ((local_34 & 0x40000) == 0) {
          if ((local_34 & 0x20000) == 0) {
            if ((local_34 & 0x10000) != 0) {
              if (sVar3 != 0) {
                uVar8 = (uint)(ushort)((short)(((int)(short)(DAT_000268b4 - uVar14) * (int)sVar3) /
                                              (int)sVar4) + uVar12);
              }
              uVar9 = (uint)DAT_000268b4;
            }
          }
          else {
            if (sVar3 != 0) {
              uVar8 = (uint)(ushort)((short)(((int)(short)(clip_top - uVar14) * (int)sVar3) /
                                            (int)sVar4) + uVar12);
            }
            uVar9 = (uint)clip_top;
          }
        }
        else {
          if (sVar4 != 0) {
            uVar9 = (uint)(ushort)((short)(((int)(short)(DAT_000268b6 - uVar12) * (int)sVar4) /
                                          (int)sVar3) + uVar14);
          }
          uVar8 = (uint)DAT_000268b6;
        }
      }
      else {
        if (sVar4 != 0) {
          uVar9 = (uint)(ushort)((short)(((int)(short)(clip_left - uVar12) * (int)sVar4) /
                                        (int)sVar3) + uVar14);
        }
        uVar8 = (uint)clip_left;
      }
      uVar12 = 10;
      if (((short)clip_left <= (short)uVar8) && (uVar12 = 2, (short)DAT_000268b6 < (short)uVar8)) {
        uVar12 = 6;
      }
      if (((short)clip_top <= (short)uVar9) &&
         (uVar12 = uVar12 & 0xfffd, (short)DAT_000268b4 < (short)uVar9)) {
        uVar12 = uVar12 | 1;
      }
      local_34 = CONCAT22(uVar12,local_34._2_2_);
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000215d8 @ 000215d8 ====

undefined2 FUN_000215d8(undefined1 *param_1,undefined4 param_2)

{
  undefined2 uVar1;
  
  DAT_00026c82 = param_1;
  uVar1 = FUN_000216b2(&LAB_00021608,param_2,&stack0x0000000c);
  *DAT_00026c82 = 0;
  return uVar1;
}


// ==== FUN_00021624 @ 00021624 ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_000216b2 @ 000216b2 ====

short FUN_000216b2(code *param_1,char *param_2,short *param_3)

{
  undefined4 uVar1;
  char cVar2;
  short sVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  char acStack_e2 [13];
  char local_d5 [187];
  char *local_1a;
  short local_16;
  short local_14;
  short local_12;
  short local_10;
  short local_e;
  ushort local_c;
  short local_a;
  short *local_8;
  
  local_a = 0;
  local_8 = param_3;
  do {
    while( true ) {
      if (*param_2 == '\0') {
        return local_a;
      }
      if (*param_2 == '%') break;
      sVar3 = (*param_1)();
      if (sVar3 == -1) {
        return -1;
      }
      local_a = local_a + 1;
      param_2 = param_2 + 1;
    }
    local_d5[1] = 0;
    local_e = 0x20;
    local_10 = 10000;
    sVar3 = (short)param_2[1];
    bVar6 = sVar3 == 0x2d;
    pcVar4 = param_2 + 2;
    if (bVar6) {
      pcVar4 = param_2 + 3;
      sVar3 = (short)param_2[2];
    }
    local_c = (ushort)!bVar6;
    pcVar5 = pcVar4;
    if (sVar3 == 0x30) {
      local_e = 0x30;
      pcVar5 = pcVar4 + 1;
      sVar3 = (short)*pcVar4;
    }
    if (sVar3 == 0x2a) {
      local_12 = *local_8;
      pcVar4 = pcVar5 + 1;
      sVar3 = (short)*pcVar5;
      local_8 = local_8 + 1;
    }
    else {
      local_12 = 0;
      pcVar4 = pcVar5;
      while (((&DAT_0002696a)[(short)(sVar3 + 1)] & 4) != 0) {
        local_12 = sVar3 + local_12 * 10 + -0x30;
        sVar3 = (short)*pcVar4;
        pcVar4 = pcVar4 + 1;
      }
    }
    if (sVar3 == 0x2e) {
      pcVar5 = pcVar4 + 1;
      sVar3 = (short)*pcVar4;
      if (sVar3 == 0x2a) {
        local_10 = *local_8;
        pcVar4 = pcVar4 + 2;
        sVar3 = (short)*pcVar5;
        local_8 = local_8 + 1;
      }
      else {
        local_10 = 0;
        pcVar4 = pcVar5;
        while (((&DAT_0002696a)[(short)(sVar3 + 1)] & 4) != 0) {
          local_10 = sVar3 + local_10 * 10 + -0x30;
          sVar3 = (short)*pcVar4;
          pcVar4 = pcVar4 + 1;
        }
      }
    }
    local_14 = 2;
    if (sVar3 == 0x6c) {
      sVar3 = (short)*pcVar4;
      local_14 = 4;
      param_2 = pcVar4 + 1;
    }
    else {
      param_2 = pcVar4;
      if (sVar3 == 0x68) {
        param_2 = pcVar4 + 1;
        sVar3 = (short)*pcVar4;
      }
    }
    switch(sVar3) {
    case 99:
      sVar3 = *local_8;
      local_8 = local_8 + 1;
    default:
      local_1a = local_d5;
      local_d5[0] = (char)sVar3;
      goto LAB_00021924;
    case 100:
      local_16 = -10;
      break;
    case 0x65:
    case 0x66:
    case 0x67:
      uVar1 = *(undefined4 *)local_8;
      local_8 = local_8 + 4;
      FUN_00021a40(uVar1,0,(short)acStack_e2,sVar3 + -0x65);
      local_1a = acStack_e2;
      pcVar4 = acStack_e2;
      do {
        pcVar5 = pcVar4 + 1;
        cVar2 = *pcVar4;
        pcVar4 = pcVar5;
      } while (cVar2 != '\0');
      local_14 = ((short)pcVar5 - (short)acStack_e2) + -1;
      local_10 = 200;
      goto LAB_00021930;
    case 0x6f:
      local_16 = 8;
      break;
    case 0x73:
      local_1a = *(char **)local_8;
      pcVar4 = local_1a;
      do {
        pcVar5 = pcVar4 + 1;
        cVar2 = *pcVar4;
        pcVar4 = pcVar5;
      } while (cVar2 != '\0');
      local_14 = ((short)pcVar5 - (short)local_1a) + -1;
      local_8 = local_8 + 2;
      goto LAB_00021930;
    case 0x75:
      local_16 = 10;
      break;
    case 0x78:
      local_16 = 0x10;
    }
    local_1a = (char *)FUN_00021624(local_8,(short)((uint)(local_d5 + 1) >> 0x10),local_14);
    local_8 = (short *)((int)local_14 + (int)local_8);
LAB_00021924:
    local_14 = ((short)local_d5 + 1) - (short)local_1a;
LAB_00021930:
    if (local_10 < local_14) {
      local_14 = local_10;
    }
    if (local_c != 0) {
      if (((*local_1a == '-') || (*local_1a == '+')) && (local_e == 0x30)) {
        local_12 = local_12 + -1;
        local_1a = local_1a + 1;
        sVar3 = (*param_1)();
        if (sVar3 == -1) {
          return -1;
        }
      }
      while (sVar3 = local_12 + -1, bVar6 = local_14 < local_12, local_12 = sVar3, bVar6) {
        sVar3 = (*param_1)();
        if (sVar3 == -1) {
          return -1;
        }
        local_a = local_a + 1;
      }
    }
    for (local_16 = 0; (*local_1a != '\0' && (local_16 < local_10)); local_16 = local_16 + 1) {
      local_1a = local_1a + 1;
      sVar3 = (*param_1)();
      if (sVar3 == -1) {
        return -1;
      }
    }
    local_a = local_16 + local_a;
    if (local_c == 0) {
      while (sVar3 = local_12 + -1, bVar6 = local_14 < local_12, local_12 = sVar3, bVar6) {
        sVar3 = (*param_1)();
        if (sVar3 == -1) {
          return -1;
        }
        local_a = local_a + 1;
      }
    }
  } while( true );
}


// ==== FUN_00021a40 @ 00021a40 ====

void FUN_00021a40(int param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  short sVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  bool bVar6;
  char cVar7;
  short local_c;
  short local_a;
  short local_6;
  
  local_c = param_4._0_2_ + 1;
  local_6 = 0;
  cVar5 = param_1 < 0;
  cVar7 = '\0';
  FUN_00021cba();
  pcVar2 = param_3;
  if (cVar7 != cVar5) {
    param_1 = FUN_00021cb0();
    pcVar2 = param_3 + 1;
    *param_3 = '-';
  }
  cVar5 = param_1 < 0;
  bVar6 = param_1 == 0;
  cVar7 = '\0';
  FUN_00021cba();
  if (!bVar6 && cVar7 == cVar5) {
    while( true ) {
      cVar5 = param_1 < 0;
      cVar7 = '\0';
      FUN_00021ca6();
      if (cVar7 == cVar5) break;
      param_1 = FUN_00021cec();
      local_6 = local_6 + -1;
    }
    while( true ) {
      cVar5 = param_1 < 0;
      cVar7 = '\0';
      FUN_00021ca6();
      if (cVar7 != cVar5) break;
      param_1 = FUN_00021cd8();
      local_6 = local_6 + 1;
    }
  }
  if (param_4._2_2_ == 2) {
    local_c = param_4._0_2_;
    if ((local_6 < -4) || (param_4._0_2_ < local_6)) {
      param_4._2_2_ = 0;
    }
  }
  else if (param_4._2_2_ == 1) {
    local_c = local_6 + local_c;
  }
  if (-1 < local_c) {
    FUN_00021c9c();
    cVar5 = DAT_0002691e < 0;
    cVar7 = '\0';
    FUN_00021ca6();
    if ((cVar7 == cVar5) && (local_6 = local_6 + 1, param_4._2_2_ != 0)) {
      local_c = local_c + 1;
    }
  }
  if (param_4._2_2_ == 0) {
    local_a = 1;
  }
  else if (local_6 < 0) {
    *pcVar2 = '0';
    pcVar3 = pcVar2 + 2;
    pcVar2[1] = '.';
    pcVar2 = pcVar3;
    sVar1 = -1 - local_6;
    if (local_c < 1) {
      sVar1 = param_4._0_2_;
    }
    while (sVar1 != 0) {
      *pcVar2 = '0';
      pcVar2 = pcVar2 + 1;
      sVar1 = sVar1 + -1;
    }
    local_a = 0;
  }
  else {
    local_a = local_6 + 1;
  }
  if (0 < local_c) {
    sVar1 = 0;
    pcVar3 = pcVar2;
    while( true ) {
      if (sVar1 < 0x10) {
        cVar5 = FUN_00021cc4();
        *pcVar3 = cVar5 + '0';
        FUN_00021ce2();
        FUN_00021cce();
        FUN_00021cec();
      }
      else {
        *pcVar3 = '0';
      }
      pcVar2 = pcVar3 + 1;
      local_c = local_c + -1;
      if (local_c == 0) break;
      pcVar4 = pcVar2;
      if ((local_a != 0) && (local_a = local_a + -1, local_a == 0)) {
        pcVar4 = pcVar3 + 2;
        *pcVar2 = '.';
      }
      sVar1 = sVar1 + 1;
      pcVar3 = pcVar4;
    }
  }
  if (param_4._2_2_ == 0) {
    *pcVar2 = 'e';
    if (local_6 < 0) {
      local_6 = -local_6;
      pcVar2[1] = '-';
    }
    else {
      pcVar2[1] = '+';
    }
    pcVar3 = pcVar2 + 2;
    if (99 < local_6) {
      pcVar3 = pcVar2 + 3;
      pcVar2[2] = (char)((int)local_6 / 100) + '0';
      local_6 = local_6 % 100;
    }
    *pcVar3 = (char)((int)local_6 / 10) + '0';
    pcVar2 = pcVar3 + 2;
    pcVar3[1] = (char)((int)local_6 % 10) + '0';
  }
  *pcVar2 = '\0';
  return;
}


// ==== FUN_00021c9c @ 00021c9c ====

void FUN_00021c9c(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021ca6 @ 00021ca6 ====

void FUN_00021ca6(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cb0 @ 00021cb0 ====

void FUN_00021cb0(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cba @ 00021cba ====

void FUN_00021cba(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cc4 @ 00021cc4 ====

void FUN_00021cc4(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cce @ 00021cce ====

void FUN_00021cce(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cd8 @ 00021cd8 ====

void FUN_00021cd8(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021ce2 @ 00021ce2 ====

void FUN_00021ce2(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cec @ 00021cec ====

void FUN_00021cec(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cf6 @ 00021cf6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021cf6(void)

{
  int iVar1;
  undefined4 in_A0;
  undefined4 unaff_A6;
  undefined4 *puVar2;
  undefined4 local_1c;
  char *pcStack_18;
  undefined4 local_14;
  undefined1 local_10 [16];
  
  if (DAT_00027efe == 0) {
    local_14 = 0;
    pcStack_18 = s_mathffp_library_00021d46;
    local_1c = 0x21d0a;
    DAT_00027efe = FUN_00021d7c();
    puVar2 = (undefined4 *)local_10;
    if (DAT_00027efe == 0) {
      local_14 = 0x10;
      pcStack_18 = &DAT_00021d56;
      local_1c = 0x21d20;
      local_1c = FUN_00021d66();
      puVar2 = &local_1c;
      FUN_00021d6e();
      (*_thunk_FUN_0001816c)();
    }
    in_A0 = *(undefined4 *)((int)puVar2 + 8);
    register0x0000003c = (BADSPACEBASE *)((int)puVar2 + 0x10);
  }
  *(undefined4 *)((int)register0x0000003c + -4) = in_A0;
  iVar1 = *(int *)register0x0000003c;
  *(undefined4 *)register0x0000003c = unaff_A6;
  *(undefined4 *)((int)register0x0000003c + -8) = 0x21d40;
  (*(code *)(DAT_00027efe + iVar1))();
  return;
}


// ==== FUN_00021d66 @ 00021d66 ====

void FUN_00021d66(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x3c))();
  return;
}


// ==== FUN_00021d6e @ 00021d6e ====

void FUN_00021d6e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x30))();
  return;
}


// ==== FUN_00021d7c @ 00021d7c ====

void FUN_00021d7c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x228))();
  return;
}


// ==== FUN_00021d92 @ 00021d92 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00021d92(void)

{
  undefined4 in_D0;
  
  (**(code **)(_DAT_00000004 + -0x204))();
  return in_D0;
}


// ==== FUN_00021da4 @ 00021da4 ====

undefined1 FUN_00021da4(char *param_1)

{
  char *extraout_A0;
  
  while (*param_1 != '\0') {
    FUN_00021d92();
    param_1 = extraout_A0;
  }
  return 0;
}


// ==== FUN_00021dc8 @ 00021dc8 ====

void FUN_00021dc8(void)

{
  FUN_00021de2();
  return;
}


// ==== FUN_00021dce @ 00021dce ====

void FUN_00021dce(void)

{
  FUN_00021de2();
  return;
}


// ==== FUN_00021de2 @ 00021de2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021de2(void)

{
  (**(code **)(_DAT_00000004 + -0x20a))();
  return;
}


// ==== FUN_00021df0 @ 00021df0 ====

void FUN_00021df0(void)

{
  FUN_00021de2();
  return;
}


// ==== FUN_00021e02 @ 00021e02 ====

char * FUN_00021e02(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  do {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  return param_1;
}


// ==== FUN_00021e12 @ 00021e12 ====

char * FUN_00021e12(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = param_1;
  do {
    pcVar2 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar2;
  } while (cVar1 != '\0');
  return pcVar2 + (-1 - (int)param_1);
}


// ==== FUN_00021e24 @ 00021e24 ====

ushort FUN_00021e24(void)

{
  int iVar1;
  
  iVar1 = FUN_000222f4();
  DAT_00026966 = iVar1 + 0x3039;
  return (ushort)((uint)(iVar1 + 0x3039) >> 0x10) & 0x7fff;
}


// ==== FUN_00021e82 @ 00021e82 ====

byte FUN_00021e82(undefined4 param_1)

{
  if ((0x40 < param_1._1_1_) && (param_1._1_1_ < 0x5b)) {
    param_1._1_1_ = param_1._1_1_ + 0x20;
  }
  return param_1._1_1_;
}


// ==== FUN_00021e9a @ 00021e9a ====

undefined4 FUN_00021e9a(byte *param_1,byte *param_2)

{
  byte bVar1;
  short sVar2;
  
  sVar2 = 0x7ffe;
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    if (*param_1 != bVar1) {
      if (*param_1 <= bVar1) {
        return 0xffffffff;
      }
      return 1;
    }
  } while ((*param_1 != 0) && (sVar2 = sVar2 + -1, param_1 = param_1 + 1, sVar2 != -1));
  return 0;
}


// ==== FUN_00021eca @ 00021eca ====

void FUN_00021eca(undefined1 *param_1,undefined1 *param_2,undefined4 param_3)

{
  if (param_2 == param_1) {
    return;
  }
  if (param_2 <= param_1) {
    while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    return;
  }
  param_1 = param_1 + param_3._0_2_;
  param_2 = param_2 + param_3._0_2_;
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    param_1 = param_1 + -1;
    param_2 = param_2 + -1;
    *param_2 = *param_1;
  }
  return;
}


// ==== FUN_00021ef4 @ 00021ef4 ====

undefined4 FUN_00021ef4(char *param_1)

{
  short sVar2;
  undefined4 uVar1;
  
  do {
    if (*param_1 == '\0') {
      uVar1 = FUN_00022474();
      return uVar1;
    }
    param_1 = param_1 + 1;
    sVar2 = FUN_00022474();
  } while (sVar2 != -1);
  return 0xffffffff;
}


// ==== FUN_00021f2e @ 00021f2e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021f2e(void)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  undefined4 extraout_A0;
  undefined4 *puVar4;
  
  uVar2 = FUN_00021fa0();
  sVar3 = 0x4e3;
  puVar4 = &DAT_00026bb0;
  do {
    *puVar4 = 0;
    iVar1 = _DAT_00000004;
    sVar3 = sVar3 + -1;
    puVar4 = puVar4 + 1;
  } while (sVar3 != -1);
  DAT_00026ec4 = _DAT_00000004;
  DAT_00027f02 = (undefined1 *)register0x0000003c;
  if ((*(byte *)(_DAT_00000004 + 0x129) & 0x10) != 0) {
    (**(code **)(_DAT_00000004 + -0x1e))(uVar2,extraout_A0);
  }
  DAT_00026e6e = (**(code **)(iVar1 + -0x198))();
  if (DAT_00026e6e == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== FUN_00021fa0 @ 00021fa0 ====

void FUN_00021fa0(void)

{
  return;
}


// ==== FUN_00021fa8 @ 00021fa8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021fa8(undefined2 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  undefined2 uVar4;
  
  DAT_00027f06 = (undefined4 *)FUN_00022d3a(DAT_00026ba4 * 6,0x10000);
  if (DAT_00027f06 == (undefined4 *)0x0) {
    FUN_00022b64(0,0);
    return;
  }
  *(undefined2 *)(DAT_00027f06 + 1) = 0;
  *(undefined2 *)(DAT_00027f06 + 4) = 1;
  *(undefined2 *)((int)DAT_00027f06 + 10) = 1;
  DAT_00027f0a = (undefined4 *)((DAT_00027f02 - *(int *)(DAT_00027f02 + 4)) + 8);
  *DAT_00027f0a = 0x4d414e58;
  iVar1 = FUN_00022d72(0);
  sVar3 = (short)iVar1;
  if (*(int *)(iVar1 + 0xac) == 0) {
    FUN_00022e00(iVar1 + 0x5c);
    DAT_00027f0e = FUN_00022da6(sVar3 + 0x5c);
    if (*(int *)(DAT_00027f0e + 0x24) != 0) {
      FUN_00022abe(**(undefined4 **)(DAT_00027f0e + 0x24));
    }
    FUN_00022318(sVar3,DAT_00027f0e);
    DAT_00027f12 = DAT_00027f0e;
  }
  else {
    FUN_000220e0(sVar3,param_1,param_2);
    DAT_00027eb8 = 1;
    *(ushort *)(DAT_00027f06 + 1) = *(ushort *)(DAT_00027f06 + 1) | 0x8000;
    *(ushort *)((int)DAT_00027f06 + 10) = *(ushort *)((int)DAT_00027f06 + 10) | 0x8000;
  }
  uVar2 = FUN_00022afa();
  *DAT_00027f06 = uVar2;
  iVar1 = FUN_00021d66();
  *(int *)((int)DAT_00027f06 + 6) = iVar1;
  if (iVar1 != 0) {
    uVar2 = FUN_00022b30(0x20de,0x3ed);
    DAT_00027f06[3] = uVar2;
  }
  uVar4 = DAT_00027f16;
  iVar1 = DAT_00027f12;
  (*_thunk_FUN_00010006)();
  FUN_00022928(uVar4,iVar1);
  return;
}


// ==== FUN_000220e0 @ 000220e0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000220e0(int param_1,short param_2,undefined2 param_3)

{
  short sVar1;
  char cVar3;
  short sVar2;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  undefined2 uVar8;
  
  pcVar4 = DAT_00026ba6;
  if (*(int *)(param_1 + 0xac) != 0) {
    pcVar4 = (char *)(*(int *)(*(int *)(param_1 + 0xac) * 4 + 0x10) << 2);
  }
  DAT_00027f18 = param_2 + *pcVar4 + 2;
  DAT_00027f1a = (char *)FUN_00022d3a(DAT_00027f18,0);
  if (DAT_00027f1a != (char *)0x0) {
    sVar1 = (short)*pcVar4;
    pcVar4 = pcVar4 + 1;
    uVar8 = (undefined2)((uint)DAT_00027f1a >> 0x10);
    sVar2 = sVar1;
    (*_thunk_FUN_000222d2)((short)DAT_00027f1a,(short)pcVar4);
    pcVar6 = DAT_00027f1a + sVar1;
    pcVar5 = &DAT_000222a6;
    do {
      cVar3 = *pcVar5;
      *pcVar6 = cVar3;
      pcVar6 = pcVar6 + 1;
      pcVar5 = pcVar5 + 1;
    } while (cVar3 != '\0');
    FUN_000222ae(DAT_00027f1a,param_3,uVar8,(short)((uint)pcVar4 >> 0x10),sVar2);
    DAT_00027f1a[sVar1] = '\0';
    DAT_00027f16 = 1;
    pcVar4 = DAT_00027f1a + sVar1 + 1;
    pcVar6 = pcVar4;
    while( true ) {
      for (; (((cVar3 = *pcVar6, cVar3 == ' ' || (cVar3 == '\t')) || (cVar3 == '\f')) ||
             ((cVar3 == '\r' || (cVar3 == '\n')))); pcVar6 = pcVar6 + 1) {
      }
      if (*pcVar6 < ' ') break;
      pcVar5 = pcVar6;
      if (*pcVar6 == '\"') {
        pcVar6 = pcVar6 + 1;
        while( true ) {
          pcVar7 = pcVar6;
          pcVar5 = pcVar4;
          pcVar6 = pcVar7 + 1;
          cVar3 = *pcVar7;
          pcVar4 = pcVar5;
          if (cVar3 == '\0') break;
          pcVar4 = pcVar5 + 1;
          *pcVar5 = cVar3;
          if (cVar3 == '\"') {
            if (*pcVar6 != '\"') {
              *pcVar5 = '\0';
              break;
            }
            pcVar6 = pcVar7 + 2;
          }
        }
      }
      else {
        while( true ) {
          pcVar6 = pcVar5 + 1;
          cVar3 = *pcVar5;
          if (((cVar3 == '\0') || (cVar3 == ' ')) ||
             ((cVar3 == '\t' || (((cVar3 == '\f' || (cVar3 == '\r')) || (cVar3 == '\n')))))) break;
          *pcVar4 = cVar3;
          pcVar4 = pcVar4 + 1;
          pcVar5 = pcVar6;
        }
        *pcVar4 = '\0';
        pcVar4 = pcVar4 + 1;
      }
      if (cVar3 == '\0') {
        pcVar6 = pcVar6 + -1;
      }
      DAT_00027f16 = DAT_00027f16 + 1;
    }
    *pcVar4 = '\0';
    DAT_00027f12 = FUN_00022d3a((DAT_00027f16 + 1) * 4,0);
    if (DAT_00027f12 == 0) {
      DAT_00027f16 = 0;
    }
    else {
      pcVar4 = DAT_00027f1a;
      for (sVar2 = 0; sVar2 < DAT_00027f16; sVar2 = sVar2 + 1) {
        *(char **)(DAT_00027f12 + sVar2 * 4) = pcVar4;
        pcVar6 = pcVar4;
        do {
          pcVar5 = pcVar6 + 1;
          cVar3 = *pcVar6;
          pcVar6 = pcVar5;
        } while (cVar3 != '\0');
        pcVar4 = pcVar4 + (short)((short)pcVar5 - (short)pcVar4);
      }
      *(undefined4 *)(DAT_00027f12 + sVar2 * 4) = 0;
    }
  }
  return;
}


// ==== FUN_000222a8 @ 000222a8 ====

char * FUN_000222a8(char *param_1,char *param_2)

{
  char cVar1;
  short sVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = param_1;
  do {
    pcVar4 = pcVar3;
    pcVar3 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  sVar2 = 0x7ffe;
  do {
    cVar1 = *param_2;
    pcVar3 = pcVar4 + 1;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') break;
    sVar2 = sVar2 + -1;
    pcVar4 = pcVar3;
    param_2 = param_2 + 1;
  } while (sVar2 != -1);
  if (cVar1 != '\0') {
    *pcVar3 = '\0';
  }
  return param_1;
}


// ==== FUN_000222ae @ 000222ae ====

char * FUN_000222ae(char *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = param_1;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  param_3._0_2_ = param_3._0_2_ + -1;
  do {
    cVar1 = *param_2;
    pcVar2 = pcVar3 + 1;
    *pcVar3 = cVar1;
    if (cVar1 == '\0') break;
    param_3._0_2_ = param_3._0_2_ + -1;
    pcVar3 = pcVar2;
    param_2 = param_2 + 1;
  } while (param_3._0_2_ != -1);
  if (cVar1 != '\0') {
    *pcVar2 = '\0';
  }
  return param_1;
}


// ==== FUN_000222d2 @ 000222d2 ====

char * FUN_000222d2(char *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  
  bVar3 = param_3._0_2_ == 0;
  pcVar2 = param_1;
  while ((!bVar3 && (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1))) {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    bVar3 = cVar1 == '\0';
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  }
  if (!bVar3) {
    param_3._0_2_ = param_3._0_2_ + 1;
  }
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    *pcVar2 = '\0';
    pcVar2 = pcVar2 + 1;
  }
  return param_1;
}


// ==== FUN_000222f4 @ 000222f4 ====

undefined8 FUN_000222f4(void)

{
  uint in_D0;
  uint in_D1;
  
  return CONCAT44((in_D1 >> 0x10) * (in_D0 & 0xffff) * 0x10000 + (in_D1 & 0xffff) * (in_D0 & 0xffff)
                  + (in_D0 >> 0x10) * (in_D1 & 0xffff) * 0x10000,in_D1);
}


// ==== FUN_00022318 @ 00022318 ====

void FUN_00022318(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  DAT_00027f1e = FUN_00021d7c(s_icon_library_000223b6,0);
  if (DAT_00027f1e != 0) {
    iVar1 = FUN_00022f10(*(undefined4 *)(*(int *)(param_2 + 0x24) + 4));
    if (iVar1 != 0) {
      iVar2 = FUN_00022ef6(*(undefined4 *)(iVar1 + 0x36),s_WINDOW_000223c3);
      if (iVar2 != 0) {
        iVar2 = FUN_00022b30(iVar2,0x3ed);
        if (iVar2 != 0) {
          *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(iVar2 * 4 + 8);
          *(int *)(param_1 + 0x9c) = iVar2;
          uVar3 = FUN_00022b30(&DAT_000223ca,0x3ed);
          *(undefined4 *)(param_1 + 0xa0) = uVar3;
        }
      }
      FUN_00022f04(iVar1);
    }
    thunk_FUN_00022b98(DAT_00027f1e);
    DAT_00027f1e = 0;
  }
  return;
}


// ==== FUN_000223cc @ 000223cc ====

undefined8 FUN_000223cc(void)

{
  int in_D0;
  int iVar1;
  int in_D1;
  bool bVar2;
  
  bVar2 = in_D0 < 0;
  if (in_D1 < 0) {
    bVar2 = !bVar2;
  }
  iVar1 = FUN_00022424();
  if (bVar2) {
    iVar1 = -iVar1;
  }
  return CONCAT44(iVar1,in_D1);
}


// ==== FUN_000223f4 @ 000223f4 ====

undefined8 FUN_000223f4(void)

{
  int iVar1;
  int in_D0;
  undefined4 in_D1;
  int extraout_D1;
  
  FUN_00022424();
  iVar1 = extraout_D1;
  if (in_D0 < 0) {
    iVar1 = -extraout_D1;
  }
  return CONCAT44(iVar1,in_D1);
}


// ==== FUN_0002240e @ 0002240e ====

undefined8 FUN_0002240e(void)

{
  undefined4 in_D1;
  undefined4 extraout_D1;
  
  FUN_00022424();
  return CONCAT44(extraout_D1,in_D1);
}


// ==== FUN_0002241a @ 0002241a ====

void FUN_0002241a(void)

{
  FUN_00022424();
  return;
}


// ==== FUN_00022424 @ 00022424 ====

undefined8 FUN_00022424(void)

{
  uint in_D0;
  uint uVar1;
  uint in_D1;
  uint uVar2;
  short sVar3;
  bool bVar4;
  
  if ((short)(in_D1 >> 0x10) != 0) {
    uVar2 = in_D0 >> 0x10;
    uVar1 = in_D0 << 0x10;
    sVar3 = 0xf;
    do {
      bVar4 = CARRY4(uVar1,uVar1);
      uVar1 = uVar1 * 2;
      uVar2 = uVar2 * 2 + (uint)bVar4;
      if (in_D1 <= uVar2) {
        uVar2 = uVar2 - in_D1;
        uVar1 = CONCAT22((short)(uVar1 >> 0x10),(short)uVar1 + 1);
      }
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
    return CONCAT44(uVar1,uVar2);
  }
  uVar1 = in_D1 & 0xffff;
  uVar2 = CONCAT22((short)((in_D0 >> 0x10) % uVar1),(short)in_D0);
  return CONCAT44(CONCAT22((short)((in_D0 >> 0x10) / uVar1),(short)(uVar2 / uVar1)),uVar2 % uVar1);
}


// ==== FUN_00022474 @ 00022474 ====

void FUN_00022474(void)

{
  FUN_0002248a();
  return;
}


// ==== FUN_0002248a @ 0002248a ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_000224cc @ 000224cc ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_00022530 @ 00022530 ====

ushort FUN_00022530(undefined4 *param_1)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = 0;
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0xffff;
  }
  else {
    if (*(char *)(param_1 + 3) != '\0') {
      if ((*(byte *)(param_1 + 3) & 4) != 0) {
        uVar1 = FUN_000225b4((short)param_1);
      }
      uVar2 = FUN_00022a62();
      uVar1 = uVar2 | uVar1;
      if ((*(byte *)(param_1 + 3) & 2) != 0) {
        FUN_000227b2((short)param_1[2]);
      }
      if ((*(byte *)(param_1 + 3) & 0x20) != 0) {
        FUN_00022856((short)*(undefined4 *)((int)param_1 + 0x12));
        FUN_000227b2((short)*(undefined4 *)((int)param_1 + 0x12));
      }
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    *(undefined1 *)(param_1 + 3) = 0;
  }
  return uVar1;
}


// ==== FUN_000225b4 @ 000225b4 ====

ushort FUN_000225b4(int *param_1,undefined4 param_2)

{
  byte *pbVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  byte local_5;
  
  uVar2 = param_2._0_2_;
  DAT_00027f22 = &LAB_00022508;
  if ((*(byte *)(param_1 + 3) & 0x10) != 0) {
    DAT_00027f22 = &LAB_00022508;
    return 0xffff;
  }
  if (((*(byte *)(param_1 + 3) & 4) == 0) ||
     (sVar4 = (short)*param_1 - (short)param_1[2],
     sVar3 = FUN_0002287a((short)((uint)param_1[2] >> 0x10),sVar4), sVar3 == sVar4)) {
    if (param_2._0_2_ == 0xffff) {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xfb;
      *param_1 = 0;
      param_1[1] = 0;
      return 0;
    }
    if (param_1[2] == 0) {
      FUN_000226ce((short)param_1);
    }
    if (*(short *)(param_1 + 4) != 1) {
      *param_1 = param_1[2];
      param_1[1] = param_1[2] + (int)*(short *)(param_1 + 4);
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 4;
      pbVar1 = (byte *)*param_1;
      *param_1 = *param_1 + 1;
      *pbVar1 = param_2._1_1_;
      return (ushort)param_2._1_1_;
    }
    local_5 = param_2._1_1_;
    sVar4 = FUN_0002287a((short)((uint)&local_5 >> 0x10),1);
    if (sVar4 == 1) {
      return uVar2;
    }
  }
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x10;
  *param_1 = 0;
  param_1[1] = 0;
  return 0xffff;
}


// ==== FUN_000226ce @ 000226ce ====

void FUN_000226ce(int param_1)

{
  int iVar1;
  short sVar2;
  
  iVar1 = FUN_0002279e();
  if (iVar1 == 0) {
    *(undefined2 *)(param_1 + 0x10) = 1;
    *(int *)(param_1 + 8) = param_1 + 0xe;
  }
  else {
    *(undefined2 *)(param_1 + 0x10) = 0x400;
    *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) | 2;
    *(int *)(param_1 + 8) = iVar1;
    sVar2 = FUN_000227fe();
    if (sVar2 != 0) {
      *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) | 0x80;
    }
  }
  return;
}


// ==== FUN_0002275e @ 0002275e ====

undefined4 * FUN_0002275e(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  DAT_00027f26 = &LAB_0002272c;
  puVar1 = (undefined4 *)FUN_00022d3a(param_1 + 8,0);
  if (puVar1 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = DAT_00026c86;
    puVar1[1] = param_1;
    puVar2 = puVar1 + 2;
    DAT_00026c86 = puVar1;
  }
  return puVar2;
}


// ==== FUN_0002279e @ 0002279e ====

void FUN_0002279e(undefined4 param_1)

{
  FUN_0002275e(param_1._0_2_);
  return;
}


// ==== FUN_000227b2 @ 000227b2 ====

undefined4 FUN_000227b2(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar1 = DAT_00026c86;
  puVar3 = (undefined4 *)0x0;
  while( true ) {
    puVar2 = puVar1;
    if (puVar2 == (undefined4 *)0x0) {
      return 0xffffffff;
    }
    if ((undefined4 *)(param_1 + -8) == puVar2) break;
    puVar1 = (undefined4 *)*puVar2;
    puVar3 = puVar2;
  }
  if (puVar3 == (undefined4 *)0x0) {
    DAT_00026c86 = (undefined4 *)*puVar2;
  }
  else {
    *puVar3 = *puVar2;
  }
  FUN_00022d8a(puVar2,puVar2[1] + 8);
  return 0;
}


// ==== FUN_000227fe @ 000227fe ====

uint FUN_000227fe(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (((param_1 < 0) || (DAT_00026ba4 <= param_1._0_2_)) ||
     (*(int *)(DAT_00027f06 + param_1._0_2_ * 6) == 0)) {
    DAT_00027f2a = 2;
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = FUN_00022b0e(*(undefined4 *)(DAT_00027f06 + param_1._0_2_ * 6));
    uVar1 = (uint)(iVar2 != 0);
  }
  return uVar1;
}


// ==== FUN_00022856 @ 00022856 ====

undefined4 FUN_00022856(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00022ace(param_1);
  if (iVar1 == 0) {
    DAT_00027f2a = FUN_00022b06();
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// ==== FUN_0002287a @ 0002287a ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_000228f8 @ 000228f8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_000228f8(void)

{
  uint uVar1;
  
  uVar1 = FUN_00022df2(0,0x1000);
  if ((uVar1 & 0x1000) != 0) {
    if (DAT_00027eb8 == 0) {
      return uVar1;
    }
    (*_thunk_FUN_0001816c)();
  }
  return 0;
}


// ==== FUN_00022928 @ 00022928 ====

void FUN_00022928(void)

{
  if (DAT_00027f22 != (code *)0x0) {
    (*DAT_00027f22)();
  }
  FUN_00022946();
  return;
}


// ==== FUN_00022946 @ 00022946 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00022946(void)

{
  short sVar1;
  undefined1 *puVar2;
  undefined2 local_10;
  undefined2 uVar3;
  
  puVar2 = &stack0xfffffffc;
  if (DAT_00027f06 != 0) {
    for (sVar1 = 0; sVar1 < DAT_00026ba4; sVar1 = sVar1 + 1) {
      FUN_00022a62();
    }
    FUN_00022d8a((short)DAT_00027f06,DAT_00026ba4 * 6);
  }
  if (DAT_00027f26 != (code *)0x0) {
    (*DAT_00027f26)();
  }
  if (DAT_00026baa != 0) {
    (*_thunk_FUN_00022b54)((short)DAT_00026baa);
  }
  if (DAT_00027f2c != (undefined4 *)0x0) {
    *DAT_00027f2c = DAT_00027f30;
  }
  if (DAT_00027f34 != 0) {
    FUN_00022b98((short)DAT_00027f34);
  }
  if (DAT_00027efe != 0) {
    FUN_00022b98((short)DAT_00027efe);
  }
  if (DAT_00027f38 != 0) {
    FUN_00022b98((short)DAT_00027f38);
  }
  if (DAT_00027f3c != 0) {
    FUN_00022b98((short)DAT_00027f3c);
  }
  if ((*(byte *)(_DAT_00000004 + 0x129) & 0x10) != 0) {
    local_10 = (undefined2)((uint)&stack0xfffffffc >> 0x10);
    uVar3 = SUB42(&stack0xfffffffc,0);
    (**(code **)(_DAT_00000004 + -0x1e))();
    puVar2 = (undefined1 *)CONCAT22(local_10,uVar3);
  }
  if (DAT_00027f0e == 0) {
    if (DAT_00027f1a != 0) {
      FUN_00022d8a((short)DAT_00027f1a,DAT_00027f18);
      FUN_00022d8a(DAT_00027f12,(int)(short)(DAT_00027f16 + 1) << 2);
    }
  }
  else {
    FUN_00022d7e();
    FUN_00022de6((short)DAT_00027f0e);
  }
  return *(undefined4 *)(puVar2 + -4);
}


// ==== FUN_00022a62 @ 00022a62 ====

undefined4 FUN_00022a62(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  piVar2 = (int *)(DAT_00027f06 + param_1._0_2_ * 6);
  if (((param_1 < 0) || (DAT_00026ba4 <= param_1._0_2_)) || (*piVar2 == 0)) {
    DAT_00027f2a = 2;
    uVar1 = 0xffffffff;
  }
  else {
    if ((*(byte *)(piVar2 + 1) & 0x80) == 0) {
      FUN_00022ab2(*piVar2);
    }
    *piVar2 = 0;
    uVar1 = 0;
  }
  return uVar1;
}


// ==== thunk_FUN_00022ab2 @ 00022aae ====

void thunk_FUN_00022ab2(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022aba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x24))();
  return;
}


// ==== FUN_00022ab2 @ 00022ab2 ====

void FUN_00022ab2(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022aba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x24))();
  return;
}


// ==== FUN_00022abe @ 00022abe ====

void FUN_00022abe(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ac6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x7e))();
  return;
}


// ==== thunk_FUN_00022ace @ 00022aca ====

void thunk_FUN_00022ace(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ad6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x48))();
  return;
}


// ==== FUN_00022ace @ 00022ace ====

void FUN_00022ace(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ad6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x48))();
  return;
}


// ==== thunk_FUN_00022ade @ 00022ada ====

void thunk_FUN_00022ade(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x66))();
  return;
}


// ==== FUN_00022ade @ 00022ade ====

void FUN_00022ade(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x66))();
  return;
}


// ==== FUN_00022aec @ 00022aec ====

void FUN_00022aec(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022af6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x6c))();
  return;
}


// ==== FUN_00022afa @ 00022afa ====

void FUN_00022afa(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022afe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x36))();
  return;
}


// ==== thunk_FUN_00022b06 @ 00022b02 ====

void thunk_FUN_00022b06(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x84))();
  return;
}


// ==== FUN_00022b06 @ 00022b06 ====

void FUN_00022b06(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x84))();
  return;
}


// ==== FUN_00022b0e @ 00022b0e ====

void FUN_00022b0e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b16. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0xd8))();
  return;
}


// ==== thunk_FUN_00022b1e @ 00022b1a ====

void thunk_FUN_00022b1e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x54))();
  return;
}


// ==== FUN_00022b1e @ 00022b1e ====

void FUN_00022b1e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x54))();
  return;
}


// ==== thunk_FUN_00022b30 @ 00022b2c ====

void thunk_FUN_00022b30(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x1e))();
  return;
}


// ==== FUN_00022b30 @ 00022b30 ====

void FUN_00022b30(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x1e))();
  return;
}


// ==== thunk_FUN_00022b42 @ 00022b3e ====

void thunk_FUN_00022b42(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x2a))();
  return;
}


// ==== FUN_00022b42 @ 00022b42 ====

void FUN_00022b42(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x2a))();
  return;
}


// ==== thunk_FUN_00022b54 @ 00022b50 ====

void thunk_FUN_00022b54(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x5a))();
  return;
}


// ==== FUN_00022b54 @ 00022b54 ====

void FUN_00022b54(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x5a))();
  return;
}


// ==== thunk_FUN_00021d6e @ 00022b60 ====

void thunk_FUN_00021d6e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x30))();
  return;
}


// ==== FUN_00022b64 @ 00022b64 ====

void FUN_00022b64(void)

{
  (**(code **)(DAT_00026ec4 + -0x6c))();
  return;
}


// ==== FUN_00022b7c @ 00022b7c ====

void FUN_00022b7c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xd8))();
  return;
}


// ==== FUN_00022b88 @ 00022b88 ====

void FUN_00022b88(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x1c2))();
  return;
}


// ==== thunk_FUN_00022b98 @ 00022b94 ====

void thunk_FUN_00022b98(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ba0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x19e))();
  return;
}


// ==== FUN_00022b98 @ 00022b98 ====

void FUN_00022b98(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ba0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x19e))();
  return;
}


// ==== FUN_00022ba4 @ 00022ba4 ====

int FUN_00022ba4(int param_1,undefined1 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00022c82(0xffffffff);
  if (iVar1 == -1) {
    iVar2 = 0;
  }
  else {
    iVar2 = thunk_FUN_00022d3a(0x22,0x10001);
    if (iVar2 == 0) {
      FUN_00022d9a(iVar1);
      iVar2 = 0;
    }
    else {
      *(int *)(iVar2 + 10) = param_1;
      *(undefined1 *)(iVar2 + 9) = param_2;
      *(undefined1 *)(iVar2 + 8) = 4;
      *(undefined1 *)(iVar2 + 0xe) = 0;
      *(char *)(iVar2 + 0xf) = (char)iVar1;
      uVar3 = thunk_FUN_00022d72(0);
      *(undefined4 *)(iVar2 + 0x10) = uVar3;
      if (param_1 == 0) {
        FUN_00022db2(iVar2 + 0x14);
      }
      else {
        FUN_00022c76(iVar2);
      }
    }
  }
  return iVar2;
}


// ==== FUN_00022c30 @ 00022c30 ====

void FUN_00022c30(int param_1)

{
  if (*(int *)(param_1 + 10) != 0) {
    FUN_00022dda(param_1);
  }
  *(undefined1 *)(param_1 + 8) = 0xff;
  *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
  FUN_00022d9a(*(undefined1 *)(param_1 + 0xf));
  thunk_FUN_00022d8a(param_1,0x22);
  return;
}


// ==== FUN_00022c76 @ 00022c76 ====

void FUN_00022c76(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022c7e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x162))();
  return;
}


// ==== FUN_00022c82 @ 00022c82 ====

void FUN_00022c82(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022c8a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x14a))();
  return;
}


// ==== FUN_00022c8e @ 00022c8e ====

void FUN_00022c8e(undefined4 param_1)

{
  FUN_00022cb6(param_1,0x30);
  return;
}


// ==== FUN_00022ca4 @ 00022ca4 ====

void FUN_00022ca4(undefined4 param_1)

{
  FUN_00022cfa(param_1);
  return;
}


// ==== FUN_00022cb6 @ 00022cb6 ====

int FUN_00022cb6(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = thunk_FUN_00022d3a(param_2,0x10001);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      *(undefined1 *)(iVar1 + 8) = 5;
      *(undefined2 *)(iVar1 + 0x12) = param_2._2_2_;
      *(int *)(iVar1 + 0xe) = param_1;
    }
  }
  return iVar1;
}


// ==== FUN_00022cfa @ 00022cfa ====

undefined4 FUN_00022cfa(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    *(undefined1 *)(param_1 + 8) = 0xff;
    *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
    uVar1 = thunk_FUN_00022d8a(param_1,*(undefined2 *)(param_1 + 0x12));
  }
  return uVar1;
}


// ==== thunk_FUN_00022d3a @ 00022d36 ====

void thunk_FUN_00022d3a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xc6))();
  return;
}


// ==== FUN_00022d3a @ 00022d3a ====

void FUN_00022d3a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xc6))();
  return;
}


// ==== FUN_00022d48 @ 00022d48 ====

void FUN_00022d48(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x78))();
  return;
}


// ==== FUN_00022d50 @ 00022d50 ====

void FUN_00022d50(void)

{
  (**(code **)(DAT_00026ec4 + -0x1c8))();
  return;
}


// ==== FUN_00022d66 @ 00022d66 ====

void FUN_00022d66(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x7e))();
  return;
}


// ==== thunk_FUN_00022d72 @ 00022d6e ====

void thunk_FUN_00022d72(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d7a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x126))();
  return;
}


// ==== FUN_00022d72 @ 00022d72 ====

void FUN_00022d72(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d7a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x126))();
  return;
}


// ==== FUN_00022d7e @ 00022d7e ====

void FUN_00022d7e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x84))();
  return;
}


// ==== thunk_FUN_00022d8a @ 00022d86 ====

void thunk_FUN_00022d8a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d96. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xd2))();
  return;
}


// ==== FUN_00022d8a @ 00022d8a ====

void FUN_00022d8a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d96. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xd2))();
  return;
}


// ==== FUN_00022d9a @ 00022d9a ====

void FUN_00022d9a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022da2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x150))();
  return;
}


// ==== FUN_00022da6 @ 00022da6 ====

void FUN_00022da6(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dae. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x174))();
  return;
}


// ==== FUN_00022db2 @ 00022db2 ====

void FUN_00022db2(int *param_1)

{
  *param_1 = (int)param_1;
  *param_1 = *param_1 + 4;
  param_1[1] = 0;
  param_1[2] = (int)param_1;
  return;
}


// ==== FUN_00022dc4 @ 00022dc4 ====

void FUN_00022dc4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dd6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x1bc))();
  return;
}


// ==== FUN_00022dda @ 00022dda ====

void FUN_00022dda(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022de2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x168))();
  return;
}


// ==== FUN_00022de6 @ 00022de6 ====

void FUN_00022de6(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x17a))();
  return;
}


// ==== FUN_00022df2 @ 00022df2 ====

void FUN_00022df2(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x132))();
  return;
}


// ==== FUN_00022e00 @ 00022e00 ====

void FUN_00022e00(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x180))();
  return;
}


// ==== FUN_00022e0c @ 00022e0c ====

void FUN_00022e0c(void)

{
  (**(code **)(DAT_00026e72 + -0x1e))();
  return;
}


// ==== FUN_00022e2e @ 00022e2e ====

void FUN_00022e2e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -300))();
  return;
}


// ==== FUN_00022e40 @ 00022e40 ====

void FUN_00022e40(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x1ce))();
  return;
}


// ==== FUN_00022e48 @ 00022e48 ====

void FUN_00022e48(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e56. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0xf6))();
  return;
}


// ==== FUN_00022e5a @ 00022e5a ====

void FUN_00022e5a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x186))();
  return;
}


// ==== FUN_00022e6c @ 00022e6c ====

void FUN_00022e6c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0xc6))();
  return;
}


// ==== FUN_00022e78 @ 00022e78 ====

void FUN_00022e78(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e86. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0xf0))();
  return;
}


// ==== FUN_00022e8a @ 00022e8a ====

void FUN_00022e8a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e8e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x1c8))();
  return;
}


// ==== FUN_00022e92 @ 00022e92 ====

void FUN_00022e92(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ea0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x132))();
  return;
}


// ==== FUN_00022ea4 @ 00022ea4 ====

void FUN_00022ea4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022eb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x156))();
  return;
}


// ==== FUN_00022eb4 @ 00022eb4 ====

void FUN_00022eb4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ec0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x15c))();
  return;
}


// ==== FUN_00022ec4 @ 00022ec4 ====

void FUN_00022ec4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x162))();
  return;
}


// ==== FUN_00022ed4 @ 00022ed4 ====

void FUN_00022ed4(void)

{
  (**(code **)(DAT_00026e72 + -0x3c))();
  return;
}


// ==== FUN_00022eee @ 00022eee ====

void FUN_00022eee(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ef2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x10e))();
  return;
}


// ==== FUN_00022ef6 @ 00022ef6 ====

void FUN_00022ef6(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00027f1e + -0x60))();
  return;
}


// ==== FUN_00022f04 @ 00022f04 ====

void FUN_00022f04(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00027f1e + -0x5a))();
  return;
}


// ==== FUN_00022f10 @ 00022f10 ====

void FUN_00022f10(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00027f1e + -0x4e))();
  return;
}


// ==== FUN_00022f1c @ 00022f1c ====

void FUN_00022f1c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e76 + -0x48))();
  return;
}


// ==== FUN_00022f28 @ 00022f28 ====

void FUN_00022f28(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e76 + -0x4e))();
  return;
}


// ==== FUN_00022f30 @ 00022f30 ====

void FUN_00022f30(void)

{
  (**(code **)(DAT_00027eba + -0x30))();
  return;
}


// ==== entry @ 00022f50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  short sVar4;
  undefined4 extraout_A0;
  undefined4 *puVar5;
  int unaff_A4;
  
  uVar2 = FUN_00021fa0();
  sVar4 = 0x4e3;
  puVar5 = (undefined4 *)(unaff_A4 + -0x439e);
  do {
    *puVar5 = 0;
    sVar4 = sVar4 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar4 != -1);
  *(BADSPACEBASE **)(unaff_A4 + -0x304c) = register0x0000003c;
  iVar1 = _DAT_00000004;
  *(int *)(unaff_A4 + -0x408a) = _DAT_00000004;
  if ((*(byte *)(iVar1 + 0x129) & 0x10) != 0) {
    (**(code **)(iVar1 + -0x1e))(uVar2,extraout_A0);
  }
  iVar3 = (**(code **)(iVar1 + -0x198))();
  *(int *)(unaff_A4 + -0x40e0) = iVar3;
  if (iVar3 == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== thunk_FUN_00010006 @ 00022f56 ====

void thunk_FUN_00010006(undefined4 param_1)

{
  short sVar1;
  char cVar2;
  int unaff_A4;
  
  DAT_00bfe001 = DAT_00bfe001 | 2;
  (**(code **)(unaff_A4 + -0x7e1e))();
  open_libraries_and_sound();
  (**(code **)(*(int *)(unaff_A4 + -0x40d8) + -0x4e))();
  *(undefined1 *)(unaff_A4 + -0x69b0) = 0xff;
  install_vbl_server();
  *(undefined2 *)(unaff_A4 + -0x6352) = 0xffff;
  if (1 < param_1._0_2_) {
    *(undefined **)(unaff_A4 + -0x4078) = &DAT_000233a8;
  }
  (**(code **)(unaff_A4 + -0x7de8))();
  init_display_memory();
  *(BADSPACEBASE **)(unaff_A4 + -0x4178) = register0x0000003c;
  FUN_000134bc();
  (**(code **)(unaff_A4 + -0x7e5a))();
LAB_00010066:
  do {
    FUN_00011234();
    *(undefined1 *)(unaff_A4 + -0x5b07) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a3e) = 0;
    *(undefined2 *)(unaff_A4 + -0x42b2) = 0;
    *(undefined2 *)(unaff_A4 + -0x42ba) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a5e) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a4a) = 0;
    new_game_init();
    *(undefined1 *)(unaff_A4 + -0x5c9c) = 0;
    *(undefined2 *)(unaff_A4 + -0x5c3c) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a3d) = 0;
    *(undefined1 *)(unaff_A4 + -0x5c7f) = 0;
    (**(code **)(unaff_A4 + -0x7e4e))();
    load_dash_shapes();
    if (*(short *)(unaff_A4 + -0x42be) == 0) {
      (**(code **)(unaff_A4 + -0x7f74))();
    }
    sVar1 = (**(code **)(unaff_A4 + -0x7e42))();
  } while (sVar1 != 0);
  (**(code **)(unaff_A4 + -0x7d8e))();
  (**(code **)(unaff_A4 + -0x7e36))();
  (**(code **)(unaff_A4 + -0x7f68))();
  FUN_0001535a();
  (**(code **)(unaff_A4 + -0x7f62))();
  if (*(short *)(unaff_A4 + -0x42be) != 0) goto LAB_000100ea;
  do {
    reset_enemy_state();
    rearm_new_plane();
    *(undefined2 *)(unaff_A4 + -0x42be) = 0;
    *(undefined1 *)(unaff_A4 + -0x5aa8) = 0;
    *(undefined2 *)(unaff_A4 + -0x42c2) = 0;
    *(undefined2 *)(unaff_A4 + -0x42bc) = 0;
LAB_000100ea:
    *(undefined1 *)(unaff_A4 + -0x69b0) = 0;
    *(undefined2 *)(unaff_A4 + -0x42be) = 0;
    (**(code **)(unaff_A4 + -0x7fbc))();
    (**(code **)(unaff_A4 + -0x7fb6))();
    if (*(short *)(unaff_A4 + -0x42b2) != 0) {
      *(undefined2 *)(unaff_A4 + -0x42ba) = 2;
    }
    *(undefined1 *)(unaff_A4 + -0x42aa) = 0xff;
LAB_0001010e:
    (**(code **)(unaff_A4 + -0x7de2))();
    if (*(char *)(unaff_A4 + -0x5c3c) != '\0') {
LAB_000101c6:
      (**(code **)(unaff_A4 + -0x7f9e))();
      clear_ticker();
      FUN_000173e6();
      *(undefined2 *)(unaff_A4 + -0x42aa) = 0;
      *(char *)(unaff_A4 + -0x4072) = -(*(short *)(unaff_A4 + -0x42b2) == 1);
      (**(code **)(unaff_A4 + -0x7e48))();
      if (*(short *)(unaff_A4 + -0x407e) != 0) {
        DAT_00bfe001 = DAT_00bfe001 & 0xfd;
        music_stop_unload();
        FUN_00011234();
        FUN_000134d8();
        return;
      }
      *(undefined1 *)(unaff_A4 + -0x69b0) = 0xff;
      *(undefined4 *)(unaff_A4 + -0x5848) = 0;
      if (*(char *)(unaff_A4 + -0x4072) == '\0') {
        FUN_00011234();
        (**(code **)(unaff_A4 + -0x7e30))();
      }
      goto LAB_00010066;
    }
    if (*(char *)(unaff_A4 + -0x5aa8) != '\0') {
      (**(code **)(unaff_A4 + -0x7e2a))();
      goto LAB_0001010e;
    }
    if ((*(char *)(unaff_A4 + -0x5c9a) == '\0') || (*(short *)(unaff_A4 + -0x5c42) == 0)) {
      frame_update_and_render();
      run_queued_logic_ticks();
      if (*(char *)(unaff_A4 + -0x5a3e) != '\0') goto LAB_00010066;
      if (((*(short *)(unaff_A4 + -0x42b2) == 1) &&
          (sVar1 = (**(code **)(unaff_A4 + -0x7d40))(), sVar1 != 0)) ||
         (*(char *)(unaff_A4 + -0x5c3c) != '\0')) goto LAB_000101c6;
      goto LAB_0001010e;
    }
    *(undefined2 *)(unaff_A4 + -0x5c42) = 0;
    *(undefined1 *)(unaff_A4 + -0x5c9a) = 0;
    (**(code **)(unaff_A4 + -0x7f9e))();
    *(undefined4 *)(unaff_A4 + -0x5848) = 0;
    clear_ticker();
    FUN_000173e6();
    FUN_00011234();
    if (*(char *)(unaff_A4 + -0x5ca1) != '\0') {
      *(char *)(unaff_A4 + -0x5ca2) = *(char *)(unaff_A4 + -0x5ca2) + '\x01';
    }
    choose_night_flag();
    (**(code **)(unaff_A4 + -0x7d8e))();
    (**(code **)(unaff_A4 + -0x7f74))();
    cVar2 = (**(code **)(unaff_A4 + -0x7e42))();
    if (cVar2 != '\0') goto LAB_00010066;
    load_dash_shapes();
    (**(code **)(unaff_A4 + -0x7e36))();
    (**(code **)(unaff_A4 + -0x7f68))();
    FUN_0001535a();
    (**(code **)(unaff_A4 + -0x7f62))();
  } while( true );
}


// ==== thunk_FUN_0001020e @ 00022f5c ====

void thunk_FUN_0001020e(void)

{
  DAT_00bfe001 = DAT_00bfe001 & 0xfd;
  music_stop_unload();
  FUN_00011234();
  FUN_000134d8();
  return;
}


// ==== thunk_FUN_0001020e @ 00022f62 ====

void thunk_FUN_0001020e(void)

{
  DAT_00bfe001 = DAT_00bfe001 & 0xfd;
  music_stop_unload();
  FUN_00011234();
  FUN_000134d8();
  return;
}


// ==== draw_player_plane @ 00022f68 ====

void draw_player_plane(void)

{
  undefined2 uVar1;
  byte bVar2;
  short sVar3;
  undefined4 uVar4;
  short sVar5;
  undefined2 extraout_D1w;
  ushort uVar6;
  short sVar7;
  ushort *puVar8;
  int unaff_A4;
  
  uVar1 = *(undefined2 *)(unaff_A4 + -0x46a0);
  if ((((*(short *)(unaff_A4 + -0x5f7a) == 1) || (*(short *)(unaff_A4 + -0x5f7a) == 7)) ||
      (*(short *)(unaff_A4 + -0x5f7a) == 0xb)) || (*(short *)(unaff_A4 + -0x5f7a) == 8)) {
LAB_0001045c:
    *(undefined2 *)(unaff_A4 + -0x419e) = *(undefined2 *)(unaff_A4 + -0x5f86);
  }
  else {
    if (*(short *)(unaff_A4 + -0x5c6a) == 1) goto LAB_000106b4;
    if ((*(short *)(unaff_A4 + -0x60ca) != 0) || ((short)*(ushort *)(unaff_A4 + -0x41a2) < 0))
    goto LAB_0001045c;
    puVar8 = (ushort *)
             ((int)(short)((*(ushort *)(unaff_A4 + -0x41a2) >> 3) * 2) +
             *(int *)(unaff_A4 + -0x69d6));
    if ((puVar8 < *(ushort **)(unaff_A4 + -0x69d2)) && ((*puVar8 & 3) == 1)) {
      (**(code **)(unaff_A4 + -0x7dee))(puVar8);
      *(undefined2 *)(unaff_A4 + -0x46a0) = 0xa1;
    }
  }
  *(undefined2 *)(unaff_A4 + -0x46a0) = 0xa1;
  if (*(short *)(unaff_A4 + -0x60c8) == 1) {
    sVar5 = *(short *)(unaff_A4 + -0x4084);
    uVar6 = *(ushort *)(unaff_A4 + -0x4086);
    if (uVar6 == 0) {
      sVar7 = -*(short *)(unaff_A4 + -0x4082) >> 2;
      if (sVar7 < -2) {
        sVar7 = -2;
      }
      if (-1 < sVar5) {
        sVar7 = sVar7 + 6;
      }
      sVar7 = sVar7 + 0x2a;
    }
    else {
      if (8 < uVar6) {
        if (uVar6 < 0x12) {
          if (0xd < uVar6) {
            sVar5 = -sVar5;
          }
          sVar7 = uVar6 + 0x2f;
          if (-1 < sVar5) {
            sVar7 = uVar6 + 0x38;
          }
          goto LAB_000104e2;
        }
        uVar6 = 0x1a - uVar6;
      }
      sVar3 = (short)(uVar6 - 1) >> 2;
      sVar7 = sVar3 + 0x34;
      if (-1 < sVar5) {
        sVar7 = sVar3 + 0x36;
      }
    }
LAB_000104e2:
    uVar4 = *(undefined4 *)(*(int *)(unaff_A4 + -0x4188) + (int)(short)(sVar7 << 2));
  }
  else {
    uVar4 = *(undefined4 *)(unaff_A4 + -0x5f82);
  }
  (**(code **)(unaff_A4 + -0x7ecc))(uVar4);
  if ((((*(short *)(unaff_A4 + -0x4086) == 0) && (*(short *)(unaff_A4 + -0x5c5a) == 2)) &&
      (*(char *)(unaff_A4 + -0x5c91) != '\0')) && (*(short *)(unaff_A4 + -0x60ca) == 0)) {
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (((*(short *)(unaff_A4 + -0x4086) == 0) && (*(short *)(unaff_A4 + -0x60ca) == 0)) &&
     ((*(short *)(unaff_A4 + -0x5f7a) == 0 ||
      ((*(short *)(unaff_A4 + -0x5f7a) == 7 || (*(short *)(unaff_A4 + -0x5562) != 0)))))) {
    sVar5 = *(short *)(unaff_A4 + -0x5cb4);
    if (sVar5 != *(short *)(unaff_A4 + -0x5bf4)) {
      if (sVar5 < *(short *)(unaff_A4 + -0x5bf4)) {
        sVar5 = sVar5 + 2;
      }
      *(short *)(unaff_A4 + -0x5cb4) = sVar5 + -1;
    }
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  (**(code **)(unaff_A4 + -0x7cd4))();
  if (*(short *)(unaff_A4 + -0x5f7a) == 7) {
    (**(code **)(unaff_A4 + -0x7c86))(extraout_D1w);
  }
  if ((((*(short *)(unaff_A4 + -0x4086) != 0) && (*(short *)(unaff_A4 + -0x5c5a) == 2)) &&
      (*(char *)(unaff_A4 + -0x5c91) != '\0')) && (*(short *)(unaff_A4 + -0x60ca) == 0)) {
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  uVar4 = (**(code **)(unaff_A4 + -0x7ed8))();
  if (((*(short *)(unaff_A4 + -0x5c94) != 0) && (*(short *)(unaff_A4 + -0x4086) == 0)) &&
     ((*(short *)(unaff_A4 + -0x60c8) != 1 &&
      (bVar2 = *(char *)(unaff_A4 + -0x5c76) + 1, *(byte *)(unaff_A4 + -0x5c76) = bVar2 & 3,
      *(char *)(unaff_A4 + -0x63f6 +
               (int)(short)((ushort)CONCAT31((int3)((uint)uVar4 >> 8),bVar2) & 0xff03)) != '\0'))))
  {
    (**(code **)(unaff_A4 + -0x7cc8))();
  }
LAB_000106b4:
  *(undefined2 *)(unaff_A4 + -0x46a0) = uVar1;
  return;
}


// ==== spawn_explosion_at_cell @ 00022f6e ====

void spawn_explosion_at_cell(short param_1,undefined4 param_2)

{
  undefined4 uVar1;
  short sVar2;
  short *psVar3;
  int unaff_A4;
  
  uVar1 = *(undefined4 *)(unaff_A4 + -0x69d6);
  psVar3 = (short *)(unaff_A4 + -0x6350);
  sVar2 = 0xe;
  while (*(char *)(psVar3 + 0x10) != '\0') {
    psVar3 = psVar3 + 0x15;
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return;
    }
  }
  psVar3[9] = 0;
  psVar3[10] = 0;
  psVar3[7] = 0;
  psVar3[8] = 0;
  *psVar3 = (param_1 - (short)uVar1) * 4;
  psVar3[2] = param_2._0_2_ + 0xc;
  psVar3[0xf] = 0;
  *(undefined1 *)(psVar3 + 0x10) = 8;
  *(undefined1 *)((int)psVar3 + 0x21) = 1;
  psVar3[0x11] = 1;
  *(undefined1 *)((int)psVar3 + 0x1f) = 0;
  if (param_2._2_2_ != 0) {
    return;
  }
  *(undefined1 *)((int)psVar3 + 0x1f) = 2;
                    /* WARNING: Could not recover jumptable at 0x00010888. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7f92))();
  return;
}


// ==== update_projectiles @ 00022f74 ====

void update_projectiles(void)

{
  short sVar1;
  int extraout_A0;
  int iVar2;
  int unaff_A4;
  
  iVar2 = unaff_A4 + -0x6350;
  sVar1 = 0xe;
  do {
    if (*(char *)(iVar2 + 0x20) != '\0') {
      update_projectile();
      iVar2 = extraout_A0;
    }
    iVar2 = iVar2 + 0x2a;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  *(undefined1 *)(unaff_A4 + -0x41c2) = 0;
  if (*(char *)(unaff_A4 + -0x5a4a) != '\0') {
    update_projectile();
  }
  return;
}


// ==== draw_enemy_planes_and_wrecks @ 00022f7a ====

undefined8 draw_enemy_planes_and_wrecks(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar2;
  int unaff_A4;
  short *psVar3;
  short *psVar4;
  
  sVar2 = *(short *)(unaff_A4 + -0x5e26);
  psVar4 = (short *)(unaff_A4 + -0x5e24);
  while (sVar2 = sVar2 + -1, sVar2 != -1) {
    psVar3 = psVar4 + 1;
    sVar1 = *psVar4;
    if (sVar1 < 0) {
      sVar1 = -sVar1;
    }
    sVar1 = sVar1 - *(short *)(unaff_A4 + -0x60ce);
    if (*(short *)(unaff_A4 + -0x60ca) != 0) {
      sVar1 = sVar1 >> 3;
    }
    psVar4 = psVar3;
    if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
      (**(code **)(unaff_A4 + -0x7cd4))();
    }
  }
  sVar2 = 3;
  psVar4 = (short *)(unaff_A4 + -0x5dd4);
  do {
    if (*psVar4 != 0) {
      sVar1 = psVar4[0x10] - *(short *)(unaff_A4 + -0x60ce);
      if (*(short *)(unaff_A4 + -0x60ca) != 0) {
        sVar1 = sVar1 >> 3;
      }
      if ((((-0x81 < sVar1) && (sVar1 < 0x1c1)) &&
          ((**(code **)(unaff_A4 + -0x7cd4))(), psVar4[9] != 0)) &&
         ((*(short *)(unaff_A4 + -0x60ca) == 0 &&
          (psVar4[0x16] = psVar4[0x16] + 1, (psVar4[0x16] & 1U) != 0)))) {
        (**(code **)(unaff_A4 + -0x7cc8))();
      }
    }
    psVar4 = psVar4 + 0x1a;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== fire_ordnance @ 00022f80 ====

undefined8 fire_ordnance(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  *(undefined1 *)(unaff_A4 + -0x5c92) = 0xff;
  fire_weapon();
  *(undefined1 *)(unaff_A4 + -0x41c1) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00011092 @ 00022f86 ====

undefined8 thunk_FUN_00011092(void)

{
  uint in_D0;
  uint in_D1;
  uint uVar1;
  int iVar2;
  
  uVar1 = (in_D1 & 0xffff) * (in_D0 & 0xffff);
  iVar2 = (int)(short)in_D1 * (int)(short)(in_D0 >> 0x10);
  if (((short)uVar1 < 0) && (uVar1 = uVar1 + 0x10000, uVar1 == 0)) {
    iVar2 = iVar2 + 1;
  }
  return CONCAT44((uVar1 >> 0x10) + iVar2,in_D1);
}


// ==== thunk_FUN_00011256 @ 00022f8c ====

void thunk_FUN_00011256(void)

{
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0xc6))();
  (**(code **)(unaff_A4 + -0x7f56))();
  (**(code **)(unaff_A4 + -0x7f5c))();
  FUN_000124e0();
  return;
}


// ==== logic_tick @ 00022f92 ====

void logic_tick(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  int unaff_A4;
  
  if (*(char *)(unaff_A4 + -0x5aa8) == '\0') {
    if (*(short *)(unaff_A4 + -0x5f7a) == 0) {
      if ((*(short *)(unaff_A4 + -0x5f74) != 0x80) &&
         (sVar1 = *(short *)(unaff_A4 + -0x3cae), sVar3 = sVar1 + -1,
         *(short *)(unaff_A4 + -0x3cae) = sVar3, sVar3 == 0 || sVar1 < 1)) {
        *(undefined2 *)(unaff_A4 + -0x3cae) = 0x50;
        *(short *)(unaff_A4 + -0x5f74) = *(short *)(unaff_A4 + -0x5f74) + -1;
      }
      sVar1 = *(short *)(unaff_A4 + -0x3cb0);
      sVar3 = sVar1 + -1;
      *(short *)(unaff_A4 + -0x3cb0) = sVar3;
      if (sVar3 == 0 || sVar1 < 1) {
        *(short *)(unaff_A4 + -0x5f78) = *(short *)(unaff_A4 + -0x5f78) + -1;
        *(undefined2 *)(unaff_A4 + -0x3cb0) = *(undefined2 *)(unaff_A4 + -0x3e96);
      }
    }
    *(short *)(unaff_A4 + -0x3cb8) = *(short *)(unaff_A4 + -0x3cb8) + 1;
    *(ushort *)(unaff_A4 + -0x3cb8) = *(ushort *)(unaff_A4 + -0x3cb8) & 1;
    sVar1 = *(short *)(unaff_A4 + -0x5c52) + -1;
    *(short *)(unaff_A4 + -0x5c52) = sVar1;
    if (sVar1 < 0) {
      *(undefined2 *)(unaff_A4 + -0x5c52) = *(undefined2 *)(unaff_A4 + -0x5c16);
      uVar2 = *(short *)(unaff_A4 + -0x6894) + 1U & 7;
      *(ushort *)(unaff_A4 + -0x6894) = uVar2;
      *(ushort *)(unaff_A4 + -0x5c50) = *(byte *)(unaff_A4 + -0x63ba + (int)(short)uVar2) + 1;
    }
    uVar4 = pop_input_queue();
    *(undefined2 *)(unaff_A4 + -0x42bc) = uVar4;
    if ((*(short *)(unaff_A4 + -0x42c0) == 0) ||
       (sVar1 = *(short *)(unaff_A4 + -0x42c0), sVar3 = sVar1 + -1,
       *(short *)(unaff_A4 + -0x42c0) = sVar3, sVar3 == 0 || sVar1 < 1)) {
      carrier_menu_input();
      carrier_phase_tick();
    }
    (**(code **)(unaff_A4 + -0x7e00))();
    (**(code **)(unaff_A4 + -0x7dd0))();
    sound_update_continuous();
    (**(code **)(unaff_A4 + -0x7e18))();
    sound_arbitrate_channels();
    snapshot_player_motion();
    oil_leak_smoke();
    (**(code **)(unaff_A4 + -0x7fda))();
    machine_gun_ground_fire();
    sVar1 = *(short *)(unaff_A4 + -0x3cb6);
    *(short *)(unaff_A4 + -0x3cb6) = sVar1 + -1;
    if (sVar1 < 1) {
      *(undefined2 *)(unaff_A4 + -0x3cb6) = 0;
    }
    update_airfields();
    update_ship_plane_launch();
    update_sinking_ships();
    update_soldiers_leaving_buildings();
    move_victory_confetti();
  }
  return;
}


// ==== input_queue_clear @ 00022f98 ====

void input_queue_clear(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3caa) = 0;
  *(undefined2 *)(unaff_A4 + -0x3ca8) = 0;
  return;
}


// ==== vbl_server @ 00022f9e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 vbl_server(void)

{
  ushort uVar1;
  byte bVar2;
  bool bVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  ushort extraout_D1w;
  undefined4 in_D1;
  short sVar7;
  undefined2 *extraout_A0;
  ushort *puVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  undefined2 *puVar11;
  undefined2 *puVar12;
  int *in_A1;
  
  vbl_flag = 0xff;
  if (paused != '\0') {
    vbl_flag = 0xff;
    return in_D1;
  }
  *in_A1 = *in_A1 + 1;
  if (DAT_000272b4 == 0) {
    (*_fire_button_debounce)();
    sVar6 = vbl_input_divider + -1;
    bVar3 = vbl_input_divider < 1;
    vbl_input_divider = sVar6;
    if (sVar6 == 0 || bVar3) {
      vbl_input_divider = 4;
      if (demo_mode == 1) {
        if ((DAT_00026ca4 == 0) || (demo_tick_budget == 0)) goto LAB_00011842;
        demo_tick_budget = demo_tick_budget + -1;
        bVar2 = *(byte *)(demo_buffer + (short)demo_pos);
        uVar5 = (ushort)bVar2;
        if ((bVar2 == 0xff) || (demo_pos = demo_pos + 1, 0x1385 < demo_pos)) {
          session_over = 0xff;
        }
        input_word = (ushort)bVar2;
      }
      else {
        uVar5 = (*_build_input_word)();
      }
      puVar11 = &input_queue;
      if (input_queue_count < 6) {
        input_queue_count = input_queue_count + 1;
      }
      else {
        uVar5 = pop_input_queue();
        puVar11 = extraout_A0;
        input_queue_count = extraout_D1w;
      }
      *(ushort *)((int)puVar11 + (int)(short)((input_queue_count - 1) * 2)) = input_word;
      if (((demo_mode == 2) && (DAT_00026ca4 != 0)) && (demo_tick_budget != 0)) {
        demo_tick_budget = demo_tick_budget + -1;
        *(undefined1 *)(demo_buffer + (short)demo_pos) = (undefined1)input_word;
        demo_pos = demo_pos + 1;
        input_word = uVar5;
        if (0x1385 < demo_pos) {
          session_over = 0xff;
        }
      }
    }
  }
LAB_00011842:
  if (not_in_game == '\0') {
    game_vbl_timer = game_vbl_timer + 1;
    if (ticker_scroll_count != 0) {
      puVar8 = (ushort *)(ticker_bitmap_ptr + 0x444);
      sVar6 = 0xc;
      ticker_scroll_count = ticker_scroll_count + -1;
      do {
        uVar5 = puVar8[-1];
        puVar8[-1] = uVar5 << 1;
        uVar1 = puVar8[-2];
        puVar8[-2] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-3];
        puVar8[-3] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-4];
        puVar8[-4] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-5];
        puVar8[-5] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-6];
        puVar8[-6] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-7];
        puVar8[-7] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-8];
        puVar8[-8] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-9];
        puVar8[-9] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-10];
        puVar8[-10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xb];
        puVar8[-0xb] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xc];
        puVar8[-0xc] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xd];
        puVar8[-0xd] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xe];
        puVar8[-0xe] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xf];
        puVar8[-0xf] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x10];
        puVar8[-0x10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x11];
        puVar8[-0x11] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x12];
        puVar8[-0x12] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x13];
        puVar8[-0x13] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x14];
        puVar8[-0x14] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x15];
        puVar8[-0x15] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x16];
        puVar8[-0x16] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x17];
        puVar8[-0x17] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x18];
        puVar8[-0x18] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x19];
        puVar8[-0x19] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1a];
        puVar8[-0x1a] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1b];
        puVar8[-0x1b] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1c];
        puVar8[-0x1c] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1d];
        puVar8[-0x1d] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1e];
        puVar8[-0x1e] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1f];
        puVar8[-0x1f] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x20];
        puVar8[-0x20] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x21];
        puVar8[-0x21] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x22];
        puVar8[-0x22] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x23];
        puVar8[-0x23] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x24];
        puVar8[-0x24] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x25];
        puVar8[-0x25] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x26];
        puVar8[-0x26] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x27];
        puVar8[-0x27] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x28];
        puVar8[-0x28] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x29];
        puVar8[-0x29] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        puVar8 = puVar8 + -0x2a;
        *puVar8 = *puVar8 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        sVar6 = sVar6 + -1;
      } while (sVar6 != -1);
      if ((ticker_char_delay != 0) &&
         (ticker_char_delay = ticker_char_delay + -1, ticker_char_delay != 0)) {
        return in_D1;
      }
    }
    if (ticker_message != (char *)0x0) {
      if (*ticker_message == '\0') {
        ticker_message = (char *)0x0;
        ticker_char_delay = 0;
      }
      else {
        ticker_scroll_count = 0x2a0;
        uVar5 = (ushort)(byte)(*ticker_message - font_first_char);
        bVar2 = *(byte *)(ticker_font + 4 + (int)(short)uVar5);
        if (bVar2 == 0) {
          ticker_char_delay = 10;
          ticker_message = ticker_message + 1;
        }
        else {
          ticker_char_delay = bVar2 + 1;
          puVar9 = (undefined2 *)
                   (*(short *)((int)&font_glyph_offsets + (int)(short)(uVar5 * 2)) + font_glyph_data
                   );
          puVar11 = (undefined2 *)(ticker_bitmap_ptr + 0x50);
          sVar6 = font_height;
          ticker_message = ticker_message + 1;
          while (sVar6 = sVar6 + -1, sVar6 != -1) {
            sVar4 = ((ushort)(bVar2 + 0xf) >> 4) - 1;
            puVar10 = puVar9;
            sVar7 = sVar4;
            do {
              puVar12 = puVar11;
              puVar9 = puVar10 + 1;
              *puVar12 = *puVar10;
              sVar7 = sVar7 + -1;
              puVar10 = puVar9;
              puVar11 = puVar12 + 1;
            } while (sVar7 != -1);
            puVar11 = (undefined2 *)((int)puVar12 + (0x54 - (short)(sVar4 * 2)));
          }
        }
      }
    }
  }
  return in_D1;
}


// ==== thunk_FUN_00011a14 @ 00022fa4 ====

void thunk_FUN_00011a14(void)

{
  undefined2 uVar1;
  undefined1 uVar2;
  short in_D0w;
  short sVar3;
  short *psVar4;
  undefined2 *extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int unaff_A4;
  
  psVar4 = *(short **)(unaff_A4 + -0x415a);
  if ((*(char *)(psVar4 + 1) == '\0') && (*psVar4 = in_D0w, in_D0w != 0)) {
    uVar2 = (**(code **)(unaff_A4 + -0x7f08))();
    *(undefined1 *)(extraout_A0_01 + 3) = uVar2;
    *(undefined1 *)(extraout_A0_01 + 2) = 4;
    return;
  }
  sVar3 = 0x12;
  do {
    if (*(char *)(psVar4 + 3) == '\0') {
      gun_ground_impact_x();
      uVar1 = kill_soldiers_near();
      *extraout_A0 = uVar1;
      (**(code **)(unaff_A4 + -0x7ec0))();
      uVar2 = (**(code **)(unaff_A4 + -0x7f08))();
      *(undefined1 *)(extraout_A0_00 + 3) = uVar2;
      return;
    }
    sVar3 = sVar3 + -1;
    psVar4 = psVar4 + 2;
  } while (sVar3 != -1);
  return;
}


// ==== thunk_FUN_00011a84 @ 00022faa ====

undefined8 thunk_FUN_00011a84(undefined4 param_1)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  short *extraout_A0;
  short *psVar2;
  int unaff_A4;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)CONCAT24(param_1._0_2_ - param_1._2_2_,(uint)(ushort)(param_1._2_2_ * 2));
  psVar2 = *(short **)(unaff_A4 + -0x5afe);
  sVar1 = *(short *)(unaff_A4 + -0x5c3a);
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if ((psVar2[3] == 1) && ((ushort)(*psVar2 - (short)(uVar3 >> 0x20)) <= (ushort)uVar3)) {
      psVar2[3] = 2;
      *(undefined1 *)((int)psVar2 + 3) = 5;
      *(undefined1 *)(psVar2 + 2) = 2;
      uVar3 = sfx_scream();
      psVar2 = extraout_A0;
    }
    psVar2 = psVar2 + 4;
  }
  destroy_torpedoes_near();
  return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),param_1._0_2_),
                  CONCAT22((short)((uint)in_D1 >> 0x10),param_1._2_2_));
}


// ==== sound_stop_all @ 00022fb0 ====

void sound_stop_all(void)

{
  short sVar1;
  undefined2 *puVar2;
  int unaff_A4;
  
  puVar2 = (undefined2 *)(unaff_A4 + -0x3c96);
  sVar1 = 7;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 0xc;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  sound_arbitrate_channels();
  return;
}


// ==== sfx_boom @ 00022fb6 ====

void sfx_boom(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x41c0) != 0) {
    *(undefined1 *)(unaff_A4 + -0x3c36) = 0xff;
    *(undefined4 *)(unaff_A4 + -0x3c26) = 0;
    uVar1 = volume_from_player_distance();
    *(undefined2 *)(unaff_A4 + -0x3c2a) = uVar1;
  }
  return;
}


// ==== sfx_boom @ 00022fbc ====

void sfx_boom(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x41c0) != 0) {
    *(undefined1 *)(unaff_A4 + -0x3c36) = 0xff;
    *(undefined4 *)(unaff_A4 + -0x3c26) = 0;
    uVar1 = volume_from_player_distance();
    *(undefined2 *)(unaff_A4 + -0x3c2a) = uVar1;
  }
  return;
}


// ==== sfx_splash @ 00022fc2 ====

void sfx_splash(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3c36) = 0;
  *(undefined1 *)(unaff_A4 + -0x3c1e) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3c26) = 0;
  uVar1 = volume_from_player_distance();
  *(undefined2 *)(unaff_A4 + -0x3c12) = uVar1;
  return;
}


// ==== sfx_metal_clang @ 00022fc8 ====

void sfx_metal_clang(void)

{
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x3bec) = *(undefined4 *)(unaff_A4 + -0x41bc);
  *(undefined2 *)(unaff_A4 + -0x3be6) = 0x1646;
  *(undefined2 *)(unaff_A4 + -0x3be4) = 0x1c2;
  *(undefined2 *)(unaff_A4 + -0x3be2) = 0x40;
  *(undefined2 *)(unaff_A4 + -0x3be0) = 1;
  *(undefined2 *)(unaff_A4 + -0x3c06) = 0;
  *(undefined1 *)(unaff_A4 + -0x3bee) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3bf6) = 0;
  return;
}


// ==== sfx_screech @ 00022fce ====

void sfx_screech(void)

{
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x3bec) = *(undefined4 *)(unaff_A4 + -0x4156);
  *(undefined2 *)(unaff_A4 + -0x3be6) = 0x1a5a;
  *(undefined2 *)(unaff_A4 + -0x3be4) = 0x15e;
  *(undefined2 *)(unaff_A4 + -0x3be2) = 0x40;
  *(undefined2 *)(unaff_A4 + -0x3be0) = 1;
  *(undefined2 *)(unaff_A4 + -0x3c06) = 0;
  *(undefined1 *)(unaff_A4 + -0x3bee) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3bf6) = 0;
  return;
}


// ==== sfx_screech @ 00022fd4 ====

void sfx_screech(void)

{
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x3bec) = *(undefined4 *)(unaff_A4 + -0x4156);
  *(undefined2 *)(unaff_A4 + -0x3be6) = 0x1a5a;
  *(undefined2 *)(unaff_A4 + -0x3be4) = 0x15e;
  *(undefined2 *)(unaff_A4 + -0x3be2) = 0x40;
  *(undefined2 *)(unaff_A4 + -0x3be0) = 1;
  *(undefined2 *)(unaff_A4 + -0x3c06) = 0;
  *(undefined1 *)(unaff_A4 + -0x3bee) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3bf6) = 0;
  return;
}


// ==== load_map @ 00022fda ====

undefined4 load_map(void)

{
  int iVar1;
  short sVar4;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_D0;
  short sVar5;
  short *psVar6;
  int unaff_A4;
  
  FUN_00013554();
  *(undefined2 *)(unaff_A4 + -0x5c3c) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c8e) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c8d) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c7a) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c7c) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c7b) = 0;
  sVar5 = *(short *)(unaff_A4 + -0x5c40);
  sVar4 = 0;
  psVar6 = (short *)(unaff_A4 + -0x5ab6);
  while (sVar5 = sVar5 + -1, sVar5 != -1) {
    sVar4 = *psVar6 + sVar4;
    psVar6 = psVar6 + 1;
  }
  uVar3 = *(undefined4 *)
           (unaff_A4 + -0x5af2 + (int)(short)((*(short *)(unaff_A4 + -0x5c3e) + sVar4 + -1) * 4));
  *(undefined4 *)(unaff_A4 + -0x69d2) = 0;
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x1e))(uVar3);
  iVar2 = *(int *)(unaff_A4 + -0x40e0);
  (**(code **)(iVar2 + -0x2a))();
  iVar1 = *(int *)(unaff_A4 + -0x410a);
  (**(code **)(iVar2 + -0x2a))();
  *(short *)(unaff_A4 + -0x5c6c) = (short)*(undefined4 *)(unaff_A4 + -0x410a) * 4 + -8;
  iVar2 = alloc_mem();
  *(int *)(unaff_A4 + -0x69d6) = iVar2;
  if (iVar2 != 0) {
    iVar2 = *(int *)(unaff_A4 + -0x40e0);
    (**(code **)(iVar2 + -0x2a))();
    (**(code **)(iVar2 + -0x24))();
    sVar5 = (short)iVar1;
    *(short *)(unaff_A4 + -0x5c38) = sVar5;
    *(short *)(unaff_A4 + -0x69ce) = sVar5 << 2;
    iVar1 = *(int *)(unaff_A4 + -0x69d6) + iVar1;
    *(uint *)(unaff_A4 + -0x69d2) = CONCAT22((short)((uint)iVar1 >> 0x10),(short)iVar1 + -2);
    parse_map_objects();
    return in_D0;
  }
  uVar3 = FUN_000124d8();
  return uVar3;
}


// ==== thunk_FUN_00012bbe @ 00022fe0 ====

undefined8 thunk_FUN_00012bbe(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  if (*(char *)(unaff_A4 + -0x5b9a) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b9a) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  if (*(char *)(unaff_A4 + -0x5b7c) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b7c) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  if (*(char *)(unaff_A4 + -0x5b5e) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b5e) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  if (*(char *)(unaff_A4 + -0x5b40) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b40) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  *(undefined1 *)(unaff_A4 + -0x5c85) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== load_ship_shapes @ 00022fe6 ====

void load_ship_shapes(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int extraout_A0_02;
  int extraout_A0_03;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x5b0a) = 0;
  if (*(char *)(unaff_A4 + -0x5c87) != '\0') {
    iVar1 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(undefined4 *)(unaff_A4 + -0x40ca) = extraout_A0;
    if (iVar1 == 0) {
      *(undefined1 *)(unaff_A4 + -0x5a3f) = 0xff;
      *(undefined1 *)(unaff_A4 + -0x5c87) = 0;
    }
    *(undefined2 *)(unaff_A4 + -0x5b64) = 0xf8;
    *(int *)(unaff_A4 + -0x40c6) = iVar1;
    alloc_ship_guns();
  }
  if (*(char *)(unaff_A4 + -0x5c84) != '\0') {
    uVar2 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(undefined2 *)(unaff_A4 + -0x5b82) = 0xd0;
    *(int *)(unaff_A4 + -0x40ba) = extraout_A0_00;
    if (extraout_A0_00 == 0) {
      FUN_000124d8();
      return;
    }
    *(undefined4 *)(unaff_A4 + -0x40b6) = uVar2;
    alloc_ship_guns();
  }
  if (*(char *)(unaff_A4 + -0x5c83) != '\0') {
    uVar2 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(undefined2 *)(unaff_A4 + -0x5b46) = 0xb8;
    *(int *)(unaff_A4 + -0x40b2) = extraout_A0_01;
    if (extraout_A0_01 == 0) {
      FUN_000124d8();
      return;
    }
    *(undefined4 *)(unaff_A4 + -0x40ae) = uVar2;
    alloc_ship_guns();
    iVar1 = *(int *)(extraout_A0_02 + 6);
    *(undefined2 *)(iVar1 + 0x14) = 5;
    *(undefined2 *)(iVar1 + 0x22) = 5;
  }
  if (*(char *)(unaff_A4 + -0x5c86) != '\0') {
    uVar2 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(int *)(unaff_A4 + -0x40c2) = extraout_A0_03;
    if (extraout_A0_03 == 0) {
      FUN_000124d8();
      return;
    }
    *(undefined2 *)(unaff_A4 + -0x5b28) = 0;
    *(undefined4 *)(unaff_A4 + -0x40be) = uVar2;
    alloc_ship_guns();
  }
  return;
}


// ==== load_sounds @ 00022fec ====

void load_sounds(void)

{
  undefined4 uVar1;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x41a6) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a84) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x41a6) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x414a) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a80) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x414a) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4156) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a74) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4156) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4152) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a7c) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4152) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x41bc) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a78) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x41bc) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x41c0) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a88) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x41c0) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4184) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a70) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4184) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4168) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a8c) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4168) = uVar1;
  }
  init_sound_slots();
  return;
}


// ==== free_sounds @ 00022ff2 ====

void free_sounds(void)

{
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  return;
}


// ==== thunk_FUN_000134ae @ 00022ff8 ====

void thunk_FUN_000134ae(void)

{
  FUN_00012502();
  return;
}


// ==== lose_life_and_respawn @ 00022ffe ====

undefined8 lose_life_and_respawn(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int iVar2;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3bac) = 0x14;
  *(char *)(unaff_A4 + -0x5ca2) = *(char *)(unaff_A4 + -0x5ca2) + -1;
  *(undefined2 *)(unaff_A4 + -0x5f84) = *(undefined2 *)(unaff_A4 + -0x5c6c);
  *(undefined2 *)(unaff_A4 + -0x5bf0) = 0;
  *(undefined2 *)(unaff_A4 + -0x5f72) = 0xffff;
  iVar2 = *(int *)(unaff_A4 + -0x40a6);
  sVar1 = 0x27;
  do {
    *(undefined2 *)(iVar2 + 0x10) = 0;
    iVar2 = iVar2 + 0x14;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if ((*(char *)(unaff_A4 + -0x5ca2) < '\x01') || (*(short *)(unaff_A4 + -0x5b1a) < 1)) {
    *(undefined1 *)(unaff_A4 + -0x5c9c) = 0xff;
    *(undefined1 *)(unaff_A4 + -0x5c3c) = 0xff;
    *(undefined1 *)(unaff_A4 + -0x5ca2) = 0;
  }
  else {
    *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
    *(undefined1 *)(unaff_A4 + -0x5c9e) = 0;
    rearm_new_plane();
    if (*(short *)(unaff_A4 + -0x3bac) != 0) {
      (**(code **)(unaff_A4 + -0x7ed8))();
      (**(code **)(unaff_A4 + -0x7ca4))();
      (**(code **)(unaff_A4 + -0x7c92))();
      (**(code **)(unaff_A4 + -0x7cbc))();
      (**(code **)(unaff_A4 + -0x7c8c))();
      FUN_0001030c();
      do {
        (**(code **)(unaff_A4 + -0x7bae))();
        sVar1 = *(short *)(unaff_A4 + -0x3bac) + -1;
        *(short *)(unaff_A4 + -0x3bac) = sVar1;
      } while (sVar1 != 0);
      do {
        (**(code **)(unaff_A4 + -0x7bae))();
      } while (*(short *)(unaff_A4 + -0x3bac) != 0);
    }
  }
  *(undefined2 *)(unaff_A4 + -0x3bac) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== clear_projectiles @ 00023004 ====

void clear_projectiles(void)

{
  short sVar1;
  int iVar2;
  int unaff_A4;
  
  iVar2 = unaff_A4 + -0x6350;
  sVar1 = 0xe;
  do {
    *(undefined1 *)(iVar2 + 0x20) = 0;
    iVar2 = iVar2 + 0x2a;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  *(undefined1 *)(unaff_A4 + -0x5a4a) = 0;
  return;
}


// ==== render_world @ 0002300a ====

void render_world(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int unaff_A4;
  ushort *puVar4;
  
  *(undefined1 *)(unaff_A4 + -0x3ba6) = 0;
  *(undefined2 *)(unaff_A4 + -0x3baa) = 0;
  *(undefined2 *)(unaff_A4 + -0x3ba8) = 10000;
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7cbc))();
  sVar2 = *(short *)(unaff_A4 + -0x5c36) + 1;
  if (sVar2 == 100) {
    sVar2 = 0;
  }
  *(short *)(unaff_A4 + -0x5c36) = sVar2;
  uVar1 = *(ushort *)(unaff_A4 + -0x41a2);
  if (*(short *)(unaff_A4 + -0x60c8) == 1) {
    uVar1 = uVar1 & 0xfff8;
  }
  sVar2 = 0x120;
  if (*(short *)(unaff_A4 + -0x60c8) != 8) {
    sVar2 = 0x900;
  }
  puVar4 = (ushort *)
           ((int)(short)((short)(uVar1 - sVar2) >> 2 & 0xfffe) + *(int *)(unaff_A4 + -0x69d6));
  sVar2 = -0x78 - (uVar1 & 7);
  *(short *)(unaff_A4 + -0x5c18) = (*(short *)(unaff_A4 + -0x419e) >> 4) + 0x18;
  if (*(short *)(unaff_A4 + -0x60c8) == 1) {
    iVar3 = *(int *)(unaff_A4 + -0x407c);
  }
  else {
    iVar3 = *(int *)(unaff_A4 + -0x40aa);
  }
  do {
    if (*(ushort **)(unaff_A4 + -0x69d6) <= puVar4) goto LAB_00013842;
    puVar4 = puVar4 + 1;
    sVar2 = *(short *)(unaff_A4 + -0x60c8) + sVar2;
  } while (sVar2 < 0x1d0);
  goto LAB_000138ba;
  while( true ) {
    uVar1 = *puVar4 >> 2;
    if (((uVar1 & 0x2000) != 0) && (*(int *)(iVar3 + (short)((uVar1 & 0x1ff) << 2)) != 0)) {
      if ((*puVar4 & 3) == 1) {
        FUN_00014eac();
      }
      (**(code **)(unaff_A4 + -0x7cd4))();
    }
    draw_special_map_cell();
    sVar2 = *(short *)(unaff_A4 + -0x60c8) + sVar2;
    puVar4 = puVar4 + 1;
    if (0x1cf < sVar2) break;
LAB_00013842:
    if (*(ushort **)(unaff_A4 + -0x69d2) < puVar4 + 1) break;
  }
LAB_000138ba:
  FUN_00013abc();
  draw_carrier_elevator();
  (**(code **)(unaff_A4 + -0x7fe6))();
  (**(code **)(unaff_A4 + -0x7fd4))();
  update_bunkers();
  update_pillboxes();
  update_ship_guns();
  draw_airfield_planes();
  draw_ship_deck_planes();
  draw_sea_waves();
  FUN_000140e8();
  (**(code **)(unaff_A4 + -0x7c8c))();
  if (*(short *)(unaff_A4 + -0x3baa) == 0) {
    *(undefined2 *)(unaff_A4 + -0x3e9a) = 0;
  }
  else {
    uVar1 = *(ushort *)(unaff_A4 + -0x3ba8) >> 3;
    if (0x40 < uVar1) {
      uVar1 = 0x40;
    }
    *(ushort *)(unaff_A4 + -0x3e98) = 0x40 - uVar1;
    *(undefined1 *)(unaff_A4 + -0x3e9a) = 0xff;
  }
  *(undefined1 *)(unaff_A4 + -0x3ba6) = 0;
  return;
}


// ==== update_draw_soldiers @ 00023010 ====

void update_draw_soldiers(void)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  char cVar7;
  short extraout_D1w;
  short sVar8;
  uint uVar9;
  int extraout_A0;
  short *psVar10;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  sVar8 = *(short *)(unaff_A4 + -0x5c3a);
  psVar10 = *(short **)(unaff_A4 + -0x5afe);
  do {
    sVar8 = sVar8 + -1;
    if (sVar8 == -1) {
LAB_00014092:
      (**(code **)(unaff_A4 + -0x7c8c))();
      return;
    }
    if (psVar10[3] != 0) {
      if (psVar10[3] != 3) {
        if (psVar10[3] == 2) {
          bVar2 = *(byte *)(psVar10 + 2) - 1;
          *(byte *)(psVar10 + 2) = bVar2;
          if ((short)((ushort)bVar2 << 8) < 0) {
            *(undefined1 *)(psVar10 + 2) = 2;
            *(char *)((int)psVar10 + 3) = *(char *)((int)psVar10 + 3) + '\x01';
            if (7 < *(byte *)((int)psVar10 + 3)) {
              psVar10[3] = 3;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x19;
              *(short *)(unaff_A4 + -0x42c2) = *(short *)(unaff_A4 + -0x42c2) + 1;
              sVar4 = (ushort)*(byte *)((int)psVar10 + 5) * 4;
              psVar1 = (short *)(unaff_A4 + -0x5bae + (int)sVar4);
              sVar6 = *psVar1 + -1;
              *psVar1 = sVar6;
              if ((sVar6 == 0) && (*(short *)(unaff_A4 + -0x5bac + (int)sVar4) == 0)) {
                uVar5 = get_island_bonus();
                uVar9 = (uint)uVar5;
                *(int *)(unaff_A4 + -0x5cb2) = uVar9 + *(int *)(unaff_A4 + -0x5cb2);
                bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
                bVar3 = bVar2 - 1;
                *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
                if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (short)((ushort)bVar3 << 8) < 0) &&
                   (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
                  (**(code **)(unaff_A4 + -0x7f1a))();
                  (**(code **)(unaff_A4 + -0x7e90))(uVar9);
                  goto LAB_00014092;
                }
                (**(code **)(unaff_A4 + -0x7e96))(uVar9);
              }
            }
          }
        }
        else {
          *(char *)((int)psVar10 + 3) = *(char *)((int)psVar10 + 3) + '\x01';
          if (4 < *(byte *)((int)psVar10 + 3)) {
            *(undefined1 *)((int)psVar10 + 3) = 0;
          }
          sVar6 = 3;
          if (*(char *)(psVar10 + 1) < '\0') {
            sVar6 = -3;
          }
          cVar7 = (**(code **)(unaff_A4 + -0x7f08))();
          if (cVar7 == '\0') {
            sVar6 = -sVar6;
            *(char *)(psVar10 + 1) = -*(char *)(psVar10 + 1);
          }
          *psVar10 = sVar6 + *psVar10;
        }
      }
      if (((((*(short *)(unaff_A4 + -0x60c8) == 8) || (psVar10[3] != 3)) &&
           ((**(code **)(unaff_A4 + -0x7eea))(), psVar10[3] == 1)) &&
          (((**(code **)(unaff_A4 + -0x7f08))(), extraout_D1w == 3 && (-1 < *psVar10)))) &&
         (cVar7 = find_ground_object_record(), -1 < cVar7)) {
        if ((*(short *)(extraout_A0 + 0xc) == 0) && (*(char *)(extraout_A0 + 8) == '\0')) {
          *(undefined2 *)(extraout_A0 + 0xc) = 0x168;
        }
        *(char *)(extraout_A0 + 8) = *(char *)(extraout_A0 + 8) + '\x01';
        psVar10[3] = 0;
      }
    }
    psVar10 = psVar10 + 4;
  } while( true );
}


// ==== draw_3d_view @ 00023016 ====

undefined8 draw_3d_view(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7ed2))();
  *(undefined2 *)(unaff_A4 + -0x5c1c) = *(undefined2 *)(unaff_A4 + -0x5c18);
  clear_3d_view();
  if (*(short *)(unaff_A4 + -0x60c8) != 1) {
    draw_3d_view_objects();
    draw_3d_view_reticle();
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return CONCAT44(in_D0,in_D1);
}


// ==== ground_impact_at_cell @ 0002301c ====

undefined8 ground_impact_at_cell(int param_1)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  ushort uVar6;
  char cVar8;
  int iVar5;
  ushort uVar7;
  ushort extraout_D1w;
  short sVar9;
  undefined4 in_D1;
  ushort uVar10;
  uint uVar11;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  int unaff_A4;
  
  param_1 = param_1 - *(int *)(unaff_A4 + -0x69d6);
  uVar6 = (short)param_1 << 2;
  *(ushort *)(unaff_A4 + -0x38fe) = uVar6;
  *(undefined2 *)(unaff_A4 + -0x38dc) = 0;
  uVar7 = *(ushort *)(unaff_A4 + -0x38fe);
  cVar8 = (**(code **)(unaff_A4 + -0x7f08))();
  if ((cVar8 == '\0') || (uVar10 = extraout_D1w & 0x1fff, cVar8 == '\x01')) {
    iVar5 = find_ship_at_x();
    if ((-1 < iVar5) && (*(short *)(unaff_A4 + -0x38dc) != 1)) {
      if (*(short *)(unaff_A4 + -0x38dc) == 2) {
        *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
        if (*(char *)(unaff_A4 + -0x38e0) == '\n') {
          *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
             (sVar9 = *(short *)(extraout_A0_02 + 0xc) + -1,
             *(short *)(extraout_A0_02 + 0xc) = sVar9, sVar9 == 0)) {
            *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
          }
          goto LAB_00014a48;
        }
      }
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
      iVar5 = *(int *)(extraout_A0_02 + 6);
      if (iVar5 != 0) {
        sVar9 = *(short *)(extraout_A0_02 + 10);
        while (sVar9 = sVar9 + -1, sVar9 != -1) {
          if (*(short *)(iVar5 + 8) == 0) {
            uVar10 = uVar7 - *(short *)(iVar5 + 4);
            if ((int)((uint)uVar10 << 0x10) < 0) {
              uVar10 = -uVar10;
            }
            if ((short)uVar10 < 0x10) {
              *(undefined2 *)(iVar5 + 8) = 0xffff;
              *(undefined2 *)(iVar5 + 10) = 0x32;
              *(undefined2 *)(iVar5 + 0xc) = 1;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
              *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
              break;
            }
          }
          iVar5 = iVar5 + 0xe;
        }
      }
    }
  }
  else {
    if (*(short *)(unaff_A4 + -0x38dc) == 0) {
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
    }
    if (uVar10 != 0x113) {
      if (uVar10 == 3) {
        cVar8 = find_ground_object_record();
        if (-1 < cVar8) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
            empty_building_soldiers();
          }
        }
      }
      else if (uVar10 == 4) {
        find_object_anchor_cells();
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        uVar7 = *(ushort *)(iVar5 + extraout_A0w);
        *(undefined2 *)(iVar5 + extraout_A0w) = 0x16;
        *(ushort *)(iVar5 + extraout_A0w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A0w);
        uVar7 = *(ushort *)(iVar5 + extraout_A1w);
        *(undefined2 *)(iVar5 + extraout_A1w) = 0x16;
        *(ushort *)(iVar5 + extraout_A1w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A1w);
        uVar7 = *(ushort *)(iVar5 + unaff_A2w);
        *(undefined2 *)(iVar5 + unaff_A2w) = 0x16;
        *(ushort *)(iVar5 + unaff_A2w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A2w);
        uVar7 = *(ushort *)(iVar5 + unaff_A3w);
        *(undefined2 *)(iVar5 + unaff_A3w) = 0x16;
        *(ushort *)(iVar5 + unaff_A3w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A3w);
        iVar5 = find_ground_object_record();
        if (-1 < iVar5) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x96;
          empty_building_soldiers();
        }
      }
      else if ((((0xe < uVar10) && (uVar10 < 0x1e)) && (*(short *)(unaff_A4 + -0x38dc) == 0)) &&
              (cVar8 = find_ground_object_record(), -1 < cVar8)) {
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
        sVar9 = *extraout_A0_01;
        find_object_anchor_cells();
        sVar9 = (1 << (4U - (((short)((uVar7 >> 2) - sVar9) >> 1) + 3) & 0x3f) | uVar10 - 0xf) + 0xf
        ;
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        *(ushort *)(iVar5 + extraout_A0w_00) =
             *(ushort *)(iVar5 + extraout_A0w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + extraout_A1w_00) =
             *(ushort *)(iVar5 + extraout_A1w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A2w) = *(ushort *)(iVar5 + unaff_A2w) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A3w) = *(ushort *)(iVar5 + unaff_A3w) & 0x8000 | sVar9 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar9 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
          psVar1 = (short *)(unaff_A4 + -0x5bac + (int)(short)(sVar9 * 4));
          sVar4 = *psVar1 + -1;
          *psVar1 = sVar4;
          if ((sVar4 == 0) && (*(short *)(unaff_A4 + -0x5bae + (int)(short)(sVar9 * 4)) == 0)) {
            uVar7 = get_island_bonus();
            uVar11 = (uint)uVar7;
            *(int *)(unaff_A4 + -0x5cb2) = uVar11 + *(int *)(unaff_A4 + -0x5cb2);
            bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
            bVar3 = bVar2 - 1;
            *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
            if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (int)((uint)bVar3 << 0x18) < 0) &&
               (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
              (**(code **)(unaff_A4 + -0x7f1a))();
              (**(code **)(unaff_A4 + -0x7e90))(uVar11);
            }
            else {
              (**(code **)(unaff_A4 + -0x7e96))(uVar11);
            }
          }
        }
      }
    }
  }
LAB_00014a48:
  return CONCAT44(CONCAT22((short)((uint)param_1 >> 0x10),uVar6),in_D1);
}


// ==== ground_impact_at_cell @ 00023022 ====

undefined8 ground_impact_at_cell(int param_1)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  ushort uVar6;
  char cVar8;
  int iVar5;
  ushort uVar7;
  ushort extraout_D1w;
  short sVar9;
  undefined4 in_D1;
  ushort uVar10;
  uint uVar11;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  int unaff_A4;
  
  param_1 = param_1 - *(int *)(unaff_A4 + -0x69d6);
  uVar6 = (short)param_1 << 2;
  *(ushort *)(unaff_A4 + -0x38fe) = uVar6;
  *(undefined2 *)(unaff_A4 + -0x38dc) = 0;
  uVar7 = *(ushort *)(unaff_A4 + -0x38fe);
  cVar8 = (**(code **)(unaff_A4 + -0x7f08))();
  if ((cVar8 == '\0') || (uVar10 = extraout_D1w & 0x1fff, cVar8 == '\x01')) {
    iVar5 = find_ship_at_x();
    if ((-1 < iVar5) && (*(short *)(unaff_A4 + -0x38dc) != 1)) {
      if (*(short *)(unaff_A4 + -0x38dc) == 2) {
        *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
        if (*(char *)(unaff_A4 + -0x38e0) == '\n') {
          *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
             (sVar9 = *(short *)(extraout_A0_02 + 0xc) + -1,
             *(short *)(extraout_A0_02 + 0xc) = sVar9, sVar9 == 0)) {
            *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
          }
          goto LAB_00014a48;
        }
      }
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
      iVar5 = *(int *)(extraout_A0_02 + 6);
      if (iVar5 != 0) {
        sVar9 = *(short *)(extraout_A0_02 + 10);
        while (sVar9 = sVar9 + -1, sVar9 != -1) {
          if (*(short *)(iVar5 + 8) == 0) {
            uVar10 = uVar7 - *(short *)(iVar5 + 4);
            if ((int)((uint)uVar10 << 0x10) < 0) {
              uVar10 = -uVar10;
            }
            if ((short)uVar10 < 0x10) {
              *(undefined2 *)(iVar5 + 8) = 0xffff;
              *(undefined2 *)(iVar5 + 10) = 0x32;
              *(undefined2 *)(iVar5 + 0xc) = 1;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
              *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
              break;
            }
          }
          iVar5 = iVar5 + 0xe;
        }
      }
    }
  }
  else {
    if (*(short *)(unaff_A4 + -0x38dc) == 0) {
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
    }
    if (uVar10 != 0x113) {
      if (uVar10 == 3) {
        cVar8 = find_ground_object_record();
        if (-1 < cVar8) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
            empty_building_soldiers();
          }
        }
      }
      else if (uVar10 == 4) {
        find_object_anchor_cells();
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        uVar7 = *(ushort *)(iVar5 + extraout_A0w);
        *(undefined2 *)(iVar5 + extraout_A0w) = 0x16;
        *(ushort *)(iVar5 + extraout_A0w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A0w);
        uVar7 = *(ushort *)(iVar5 + extraout_A1w);
        *(undefined2 *)(iVar5 + extraout_A1w) = 0x16;
        *(ushort *)(iVar5 + extraout_A1w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A1w);
        uVar7 = *(ushort *)(iVar5 + unaff_A2w);
        *(undefined2 *)(iVar5 + unaff_A2w) = 0x16;
        *(ushort *)(iVar5 + unaff_A2w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A2w);
        uVar7 = *(ushort *)(iVar5 + unaff_A3w);
        *(undefined2 *)(iVar5 + unaff_A3w) = 0x16;
        *(ushort *)(iVar5 + unaff_A3w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A3w);
        iVar5 = find_ground_object_record();
        if (-1 < iVar5) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x96;
          empty_building_soldiers();
        }
      }
      else if ((((0xe < uVar10) && (uVar10 < 0x1e)) && (*(short *)(unaff_A4 + -0x38dc) == 0)) &&
              (cVar8 = find_ground_object_record(), -1 < cVar8)) {
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
        sVar9 = *extraout_A0_01;
        find_object_anchor_cells();
        sVar9 = (1 << (4U - (((short)((uVar7 >> 2) - sVar9) >> 1) + 3) & 0x3f) | uVar10 - 0xf) + 0xf
        ;
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        *(ushort *)(iVar5 + extraout_A0w_00) =
             *(ushort *)(iVar5 + extraout_A0w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + extraout_A1w_00) =
             *(ushort *)(iVar5 + extraout_A1w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A2w) = *(ushort *)(iVar5 + unaff_A2w) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A3w) = *(ushort *)(iVar5 + unaff_A3w) & 0x8000 | sVar9 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar9 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
          psVar1 = (short *)(unaff_A4 + -0x5bac + (int)(short)(sVar9 * 4));
          sVar4 = *psVar1 + -1;
          *psVar1 = sVar4;
          if ((sVar4 == 0) && (*(short *)(unaff_A4 + -0x5bae + (int)(short)(sVar9 * 4)) == 0)) {
            uVar7 = get_island_bonus();
            uVar11 = (uint)uVar7;
            *(int *)(unaff_A4 + -0x5cb2) = uVar11 + *(int *)(unaff_A4 + -0x5cb2);
            bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
            bVar3 = bVar2 - 1;
            *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
            if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (int)((uint)bVar3 << 0x18) < 0) &&
               (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
              (**(code **)(unaff_A4 + -0x7f1a))();
              (**(code **)(unaff_A4 + -0x7e90))(uVar11);
            }
            else {
              (**(code **)(unaff_A4 + -0x7e96))(uVar11);
            }
          }
        }
      }
    }
  }
LAB_00014a48:
  return CONCAT44(CONCAT22((short)((uint)param_1 >> 0x10),uVar6),in_D1);
}


// ==== weapon_impact_ground_objects @ 00023028 ====

undefined8 weapon_impact_ground_objects(void)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  char cVar7;
  int iVar5;
  ushort uVar6;
  undefined4 in_D0;
  ushort extraout_D1w;
  short sVar8;
  undefined4 in_D1;
  ushort uVar9;
  uint uVar10;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  ushort *in_A0;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  int unaff_A4;
  
  uVar6 = *in_A0;
  cVar7 = (**(code **)(unaff_A4 + -0x7f08))();
  if ((cVar7 == '\0') || (uVar9 = extraout_D1w & 0x1fff, cVar7 == '\x01')) {
    iVar5 = find_ship_at_x();
    if ((-1 < iVar5) && (in_A0[0x11] != 1)) {
      if (in_A0[0x11] == 2) {
        *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
        if (*(char *)(in_A0 + 0xf) == '\n') {
          *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
             (sVar8 = *(short *)(extraout_A0_02 + 0xc) + -1,
             *(short *)(extraout_A0_02 + 0xc) = sVar8, sVar8 == 0)) {
            *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
          }
          goto LAB_00014a48;
        }
      }
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
      iVar5 = *(int *)(extraout_A0_02 + 6);
      if (iVar5 != 0) {
        sVar8 = *(short *)(extraout_A0_02 + 10);
        while (sVar8 = sVar8 + -1, sVar8 != -1) {
          if (*(short *)(iVar5 + 8) == 0) {
            uVar9 = uVar6 - *(short *)(iVar5 + 4);
            if ((int)((uint)uVar9 << 0x10) < 0) {
              uVar9 = -uVar9;
            }
            if ((short)uVar9 < 0x10) {
              *(undefined2 *)(iVar5 + 8) = 0xffff;
              *(undefined2 *)(iVar5 + 10) = 0x32;
              *(undefined2 *)(iVar5 + 0xc) = 1;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
              *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
              break;
            }
          }
          iVar5 = iVar5 + 0xe;
        }
      }
    }
  }
  else {
    if (in_A0[0x11] == 0) {
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
    }
    if (uVar9 != 0x113) {
      if (uVar9 == 3) {
        cVar7 = find_ground_object_record();
        if (-1 < cVar7) {
          if (in_A0[0x11] == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
            empty_building_soldiers();
          }
        }
      }
      else if (uVar9 == 4) {
        find_object_anchor_cells();
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        uVar6 = *(ushort *)(iVar5 + extraout_A0w);
        *(undefined2 *)(iVar5 + extraout_A0w) = 0x16;
        *(ushort *)(iVar5 + extraout_A0w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + extraout_A0w);
        uVar6 = *(ushort *)(iVar5 + extraout_A1w);
        *(undefined2 *)(iVar5 + extraout_A1w) = 0x16;
        *(ushort *)(iVar5 + extraout_A1w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + extraout_A1w);
        uVar6 = *(ushort *)(iVar5 + unaff_A2w);
        *(undefined2 *)(iVar5 + unaff_A2w) = 0x16;
        *(ushort *)(iVar5 + unaff_A2w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + unaff_A2w);
        uVar6 = *(ushort *)(iVar5 + unaff_A3w);
        *(undefined2 *)(iVar5 + unaff_A3w) = 0x16;
        *(ushort *)(iVar5 + unaff_A3w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + unaff_A3w);
        iVar5 = find_ground_object_record();
        if (-1 < iVar5) {
          if (in_A0[0x11] == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x96;
          empty_building_soldiers();
        }
      }
      else if ((((0xe < uVar9) && (uVar9 < 0x1e)) && (in_A0[0x11] == 0)) &&
              (cVar7 = find_ground_object_record(), -1 < cVar7)) {
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
        sVar8 = *extraout_A0_01;
        find_object_anchor_cells();
        sVar8 = (1 << (4U - (((short)((uVar6 >> 2) - sVar8) >> 1) + 3) & 0x3f) | uVar9 - 0xf) + 0xf;
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        *(ushort *)(iVar5 + extraout_A0w_00) =
             *(ushort *)(iVar5 + extraout_A0w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar5 + extraout_A1w_00) =
             *(ushort *)(iVar5 + extraout_A1w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A2w) = *(ushort *)(iVar5 + unaff_A2w) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A3w) = *(ushort *)(iVar5 + unaff_A3w) & 0x8000 | sVar8 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar8 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
          psVar1 = (short *)(unaff_A4 + -0x5bac + (int)(short)(sVar8 * 4));
          sVar4 = *psVar1 + -1;
          *psVar1 = sVar4;
          if ((sVar4 == 0) && (*(short *)(unaff_A4 + -0x5bae + (int)(short)(sVar8 * 4)) == 0)) {
            uVar6 = get_island_bonus();
            uVar10 = (uint)uVar6;
            *(int *)(unaff_A4 + -0x5cb2) = uVar10 + *(int *)(unaff_A4 + -0x5cb2);
            bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
            bVar3 = bVar2 - 1;
            *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
            if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (int)((uint)bVar3 << 0x18) < 0) &&
               (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
              (**(code **)(unaff_A4 + -0x7f1a))();
              (**(code **)(unaff_A4 + -0x7e90))(uVar10);
            }
            else {
              (**(code **)(unaff_A4 + -0x7e96))(uVar10);
            }
          }
        }
      }
    }
  }
LAB_00014a48:
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00015076 @ 0002302e ====

void thunk_FUN_00015076(void)

{
  return;
}


// ==== format_string @ 00023034 ====

undefined4 format_string(void)

{
  undefined4 in_D0;
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x20a))();
  return in_D0;
}


// ==== thunk_FUN_00015094 @ 0002303a ====

undefined4 thunk_FUN_00015094(void)

{
  undefined4 in_D0;
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x20a))();
  return in_D0;
}


// ==== present_frame @ 00023040 ====

undefined8 present_frame(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  flip_views(*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_0001520c();
  return CONCAT44(in_D0,in_D1);
}


// ==== map_cell_at_x @ 00023046 ====

ulonglong map_cell_at_x(void)

{
  ushort uVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  uVar1 = (ushort)in_D0;
  if ((-1 < (short)uVar1) && (uVar1 < *(ushort *)(unaff_A4 + -0x69ce))) {
    uVar1 = *(ushort *)(*(int *)(unaff_A4 + -0x69d6) + (int)(short)((uVar1 >> 3) * 2));
    return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),uVar1),
                    CONCAT22((short)((uint)in_D1 >> 0x10),uVar1 >> 2)) & 0xffff0003ffff01ff;
  }
  return 0;
}


// ==== thunk_FUN_00015102 @ 0002304c ====

void thunk_FUN_00015102(void)

{
  return;
}


// ==== cos_lookup @ 00023052 ====

short cos_lookup(void)

{
  ushort uVar1;
  ushort uVar2;
  short in_D0w;
  int unaff_A4;
  
  uVar2 = in_D0w + 0x100U & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar2 * 2));
}


// ==== sin_lookup @ 00023058 ====

short sin_lookup(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort in_D0w;
  int unaff_A4;
  
  uVar2 = in_D0w & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar2 * 2));
}


// ==== tan_lookup @ 0002305e ====

undefined6 tan_lookup(void)

{
  ushort uVar1;
  short sVar2;
  ushort in_D0w;
  undefined4 in_D1;
  int unaff_A4;
  
  uVar1 = in_D0w;
  if ((short)in_D0w < 0) {
    uVar1 = -in_D0w;
  }
  sVar2 = *(short *)(unaff_A4 + -0x6892 + (int)(short)((uVar1 & 0xff) * 2));
  if ((short)in_D0w < 0) {
    sVar2 = -sVar2;
  }
  return CONCAT24(sVar2,in_D1);
}


// ==== draw_world_object @ 00023064 ====

undefined8 draw_world_object(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  sVar1 = (short)in_D0 - *(short *)(unaff_A4 + -0x60ce);
  if (*(short *)(unaff_A4 + -0x60ca) != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== draw_world_object_xor @ 0002306a ====

undefined8 draw_world_object_xor(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  sVar1 = (short)in_D0 - *(short *)(unaff_A4 + -0x60ce);
  if (*(short *)(unaff_A4 + -0x60ca) != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (**(code **)(unaff_A4 + -0x7cc8))();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== read_joystick_dirs @ 00023070 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined6 read_joystick_dirs(void)

{
  byte bVar1;
  ushort uVar2;
  undefined4 in_D1;
  int unaff_A4;
  
  bVar1 = *(byte *)(unaff_A4 + -0x5958 + (int)(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3))
  ;
  uVar2 = (ushort)bVar1;
  if (((bVar1 & 3) != 0) && (*(char *)(unaff_A4 + -0x5b08) != '\0')) {
    uVar2 = uVar2 ^ 3;
  }
  return CONCAT24(uVar2,in_D1);
}


// ==== clip_playfield @ 00023076 ====

void clip_playfield(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return;
}


// ==== clip_3d_view @ 0002307c ====

void clip_3d_view(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return;
}


// ==== clip_to_deck @ 00023082 ====

undefined8 clip_to_deck(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_000152ac @ 00023088 ====

undefined2 thunk_FUN_000152ac(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  int unaff_A4;
  
  puVar3 = *(undefined2 **)(unaff_A4 + -0x40ce);
  sVar2 = 0x14;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return param_1._0_2_;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = param_1._0_2_;
  cVar1 = map_cell_at_x();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return param_1._0_2_;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return param_1._0_2_;
}


// ==== add_gun_impact @ 0002308e ====

undefined4 add_gun_impact(void)

{
  char cVar1;
  undefined4 in_D0;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  int unaff_A4;
  
  puVar3 = *(undefined2 **)(unaff_A4 + -0x40ce);
  sVar2 = 0x14;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return in_D0;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = (short)in_D0;
  cVar1 = map_cell_at_x();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return in_D0;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return in_D0;
}


// ==== draw_splashes @ 00023094 ====

undefined8 draw_splashes(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  int extraout_A1;
  int iVar2;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  iVar2 = *(int *)(unaff_A4 + -0x40ce);
  sVar1 = 0x14;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if (*(char *)(iVar2 + 2) != '\0') {
      draw_world_object();
      *(char *)(extraout_A1 + 2) = *(char *)(extraout_A1 + 2) + -1;
      iVar2 = extraout_A1;
    }
    iVar2 = iVar2 + 4;
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0001535a @ 0002309a ====

undefined8 thunk_FUN_0001535a(void)

{
  short sVar2;
  undefined4 uVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int unaff_A4;
  undefined4 *puVar8;
  
  sVar2 = 0xb7;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x41b4);
  puVar5 = *(undefined4 **)(unaff_A4 + -0x407c);
  puVar7 = *(undefined4 **)(unaff_A4 + -0x4188);
  puVar6 = *(undefined4 **)(unaff_A4 + -0x40aa);
  do {
    puVar8 = puVar6;
    puVar4 = puVar5;
    puVar6 = puVar8 + 1;
    *puVar8 = *puVar3;
    puVar5 = puVar4 + 1;
    *puVar4 = *puVar7;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
    puVar7 = puVar7 + 1;
  } while (sVar2 != -1);
  sVar2 = 0x17;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40ae);
  if (*(undefined4 **)(unaff_A4 + -0x40ae) == (undefined4 *)0x0) {
    puVar8 = puVar8 + 2;
    *puVar6 = 0;
    puVar4 = puVar4 + 2;
    *puVar5 = 0;
  }
  else {
    do {
      puVar8 = puVar6 + 1;
      *puVar6 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      puVar4 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar4;
      puVar6 = puVar8;
    } while (sVar2 != -1);
  }
  sVar2 = 0x1a;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40b6);
  if (*(undefined4 **)(unaff_A4 + -0x40b6) == (undefined4 *)0x0) {
    puVar7 = puVar8 + 1;
    *puVar8 = 0;
    puVar5 = puVar4 + 1;
    *puVar4 = 0;
  }
  else {
    do {
      puVar7 = puVar8 + 1;
      *puVar8 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      puVar5 = puVar4 + 1;
      *puVar4 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar4 = puVar5;
      puVar8 = puVar7;
    } while (sVar2 != -1);
  }
  sVar2 = 0xc;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40be);
  if (*(char *)(unaff_A4 + -0x5c86) == '\0') {
    puVar4 = puVar7 + 1;
    *puVar7 = 0;
    puVar6 = puVar5 + 1;
    *puVar5 = 0;
  }
  else {
    do {
      puVar4 = puVar7 + 1;
      *puVar7 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      puVar6 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar6;
      puVar7 = puVar4;
    } while (sVar2 != -1);
  }
  sVar2 = 0x18;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40c6);
  if (*(undefined4 **)(unaff_A4 + -0x40c6) == (undefined4 *)0x0) {
    *puVar4 = 0;
    *puVar6 = 0;
  }
  else {
    do {
      *puVar4 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      *puVar6 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
      puVar4 = puVar4 + 1;
    } while (sVar2 != -1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== spawn_smoke_particle @ 000230a0 ====

void spawn_smoke_particle(void)

{
  uint uVar1;
  undefined4 in_D0;
  int in_D1;
  undefined2 unaff_D2w;
  short sVar2;
  undefined4 *puVar3;
  int extraout_A0;
  int extraout_A0_00;
  int unaff_A4;
  
  sVar2 = 0x27;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40a6);
  do {
    if (*(short *)(puVar3 + 4) == 0) {
      *puVar3 = in_D0;
      if (in_D1 < 0x100000) {
        in_D1 = 0x100000;
      }
      puVar3[1] = in_D1;
      *(undefined2 *)(puVar3 + 4) = unaff_D2w;
      *(undefined2 *)((int)puVar3 + 0x12) = 6;
      uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
      *(uint *)(extraout_A0 + 8) = (uVar1 & 0xffff) + 0x10000;
      uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
      *(uint *)(extraout_A0_00 + 0xc) = (uVar1 & 0xffff) + 0x10000;
      return;
    }
    puVar3 = puVar3 + 5;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}


// ==== ticker_start_message @ 000230a6 ====

undefined4 ticker_start_message(void)

{
  undefined4 in_A0;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x5848) == 0) {
    *(undefined4 *)(unaff_A4 + -0x5848) = in_A0;
    return 0;
  }
  return 0xffffffff;
}


// ==== thunk_FUN_0001556e @ 000230ac ====

void thunk_FUN_0001556e(void)

{
  int unaff_A4;
  
  if (*(short *)(unaff_A4 + -0x6352) != 0) {
                    /* WARNING: Could not recover jumptable at 0x00015576. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(unaff_A4 + -0x7c7a))();
    return;
  }
  return;
}


// ==== draw_balloons @ 000230b2 ====

void draw_balloons(void)

{
  ushort uVar2;
  char cVar3;
  uint uVar1;
  char cVar4;
  short *psVar5;
  int unaff_A4;
  
  if ((*(char *)(unaff_A4 + -0x5ca1) != '\0') && (*(short *)(unaff_A4 + -0x60c8) == 8)) {
    psVar5 = *(short **)(unaff_A4 + -0x4098);
    cVar4 = '\0';
    (**(code **)(unaff_A4 + -0x7c92))();
    do {
      if (*(char *)((int)psVar5 + 0x11) == '\0') {
        *psVar5 = *(short *)(unaff_A4 + -0x5c6c);
        *psVar5 = *psVar5 + -0x74;
        psVar5[2] = 0x38;
        uVar2 = (**(code **)(unaff_A4 + -0x7d4c))();
        uVar2 = uVar2 >> 0xc & 3;
        cVar3 = (char)uVar2;
        if (uVar2 == 0) {
          cVar3 = '\x02';
        }
        *(char *)(psVar5 + 8) = cVar3 + -1;
        uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
        *(uint *)(psVar5 + 4) = (uVar1 & 0xffff) * 2 + 0x10000;
        uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
        *(uint *)(psVar5 + 6) = (uVar1 & 0xffff) * 2 + 0x10000;
        *(undefined1 *)((int)psVar5 + 0x11) = 0xff;
      }
      draw_world_object();
      psVar5 = psVar5 + 9;
      cVar4 = cVar4 + '\x01';
    } while (cVar4 != '\x14');
    (**(code **)(unaff_A4 + -0x7c8c))();
  }
  return;
}


// ==== ticker_printf @ 000230b8 ====

void ticker_printf(void)

{
  format_string();
  ticker_start_message();
  return;
}


// ==== advance_mission @ 000230be ====

undefined4 advance_mission(void)

{
  char cVar1;
  undefined4 in_D0;
  char *pcVar2;
  int unaff_A4;
  
  *(short *)(unaff_A4 + -0x5c3e) = *(short *)(unaff_A4 + -0x5c3e) + 1;
  if (*(short *)(unaff_A4 + -0x5ab6 + (int)(short)(*(short *)(unaff_A4 + -0x5c40) * 2)) <
      *(short *)(unaff_A4 + -0x5c3e)) {
    *(undefined2 *)(unaff_A4 + -0x5c3e) = 1;
    *(short *)(unaff_A4 + -0x5c40) = *(short *)(unaff_A4 + -0x5c40) + 1;
    if (6 < *(short *)(unaff_A4 + -0x5c40)) {
      *(undefined2 *)(unaff_A4 + -0x5c40) = 6;
    }
    *(undefined1 *)(unaff_A4 + -0x5ca1) = 0xff;
    pcVar2 = (char *)(unaff_A4 + -0x3e94);
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    format_string();
  }
  else {
    pcVar2 = (char *)(unaff_A4 + -0x3e94);
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    format_string();
  }
  *(undefined1 **)(unaff_A4 + -0x5848) = &message_buffer;
  *(undefined2 *)(unaff_A4 + -0x5c42) = 0xffff;
  return in_D0;
}


// ==== load_shape_bank @ 000230c4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong load_shape_bank(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 unaff_D5w;
  undefined4 *puVar3;
  undefined4 in_A0;
  int *piVar4;
  int *in_A1;
  undefined4 *puVar5;
  int unaff_A4;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  
  *(undefined4 *)(unaff_A4 + -0x595c) = in_A0;
  piVar4 = in_A1;
  do {
    iVar1 = *piVar4;
    piVar4 = piVar4 + 1;
  } while (iVar1 != 0);
  uVar6 = FUN_00015d50();
  uVar2 = (undefined4)uVar6;
  if ((int)((ulonglong)uVar6 >> 0x20) != 0) {
    puVar3 = (undefined4 *)0x0;
    if (in_A1 != (int *)0x0) {
      uVar6 = alloc_mem(unaff_D5w);
      puVar3 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
      uVar2 = (undefined4)uVar6;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        while( true ) {
          puVar5 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
          uVar2 = (undefined4)uVar6;
          if (*in_A1 == 0) break;
          uVar8 = (**(code **)(unaff_A4 + -0x7d28))();
          uVar6 = CONCAT44(puVar5 + 1,(int)uVar8);
          *puVar5 = (int)((ulonglong)uVar8 >> 0x20);
          in_A1 = in_A1 + 1;
        }
      }
    }
    return CONCAT44(puVar3,uVar2);
  }
  uVar7 = (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x84))();
  (**(code **)(_DAT_00000004 + -0x20a))((int)(uVar7 >> 0x20));
  return uVar7 & 0xffffffff;
}


// ==== thunk_FUN_00015c5c @ 000230ca ====

undefined4 * thunk_FUN_00015c5c(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *in_A1;
  undefined4 *puVar3;
  int unaff_A4;
  
  puVar2 = (undefined4 *)0x0;
  if ((in_A1 != (int *)0x0) && (puVar2 = (undefined4 *)alloc_mem(), puVar2 != (undefined4 *)0x0)) {
    *puVar2 = 0;
    puVar3 = puVar2;
    while (*in_A1 != 0) {
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
      in_A1 = in_A1 + 1;
    }
  }
  return puVar2;
}


// ==== thunk_FUN_00015d5a @ 000230d0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 thunk_FUN_00015d5a(void)

{
  return _DAT_00dff006;
}


// ==== text_input_field @ 000230d6 ====

undefined2 text_input_field(undefined1 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  uint uVar1;
  ushort uVar5;
  int unaff_A4;
  undefined2 uVar6;
  undefined2 uStack_68;
  short sStack_5e;
  undefined1 uStack_5b;
  short sStack_5a;
  short sStack_58;
  short sStack_56;
  undefined1 auStack_54 [80];
  
  uStack_68 = 0;
  (**(code **)(unaff_A4 + -0x7bc6))((short)*(undefined4 *)(unaff_A4 + -0x40e4),6);
  (**(code **)(unaff_A4 + -0x7bc0))((short)*(undefined4 *)(unaff_A4 + -0x40e4),0);
  (**(code **)(unaff_A4 + -0x7bba))((short)*(undefined4 *)(unaff_A4 + -0x40e4),1);
  sStack_5a = 0;
  do {
    auStack_54[sStack_5a] = 0x20;
    sStack_5a = sStack_5a + 1;
  } while (sStack_5a < 0x50);
  sStack_58 = -1;
  sStack_56 = 0;
  while( true ) {
    while( true ) {
      while( true ) {
        if (((sStack_56 != sStack_58) && (sStack_5e == 0)) && (-1 < sStack_58)) {
          FUN_00016032(param_3._0_2_);
        }
        uVar6 = SUB42(param_1,0);
        if (sStack_5e != 0) {
          (**(code **)(unaff_A4 + -0x7bd2))
                    ((short)*(undefined4 *)(unaff_A4 + -0x40e4),param_2._2_2_,
                     param_3._0_2_ + *(short *)(*(int *)(unaff_A4 + -0x40e4) + 0x3e));
          uVar2 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
          (**(code **)(unaff_A4 + -0x7bb4))((short)*(undefined4 *)(unaff_A4 + -0x40e4),uVar6,uVar2);
          sVar3 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
          if (sVar3 <= param_2._0_2_) {
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0;
            sVar3 = (**(code **)(unaff_A4 + -0x7c6e))
                              (uVar6,param_3._0_2_ + *(short *)(*(int *)(unaff_A4 + -0x40e4) + 0x3e)
                              );
            (**(code **)(unaff_A4 + -0x7bd2))
                      ((short)*(undefined4 *)(unaff_A4 + -0x40e4),param_2._2_2_ + sVar3 * 8);
            uVar2 = (**(code **)(unaff_A4 + -0x7c6e))((short)auStack_54);
            (**(code **)(unaff_A4 + -0x7bb4))
                      ((short)*(undefined4 *)(unaff_A4 + -0x40e4),(short)auStack_54,uVar2);
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0x20;
          }
        }
        if ((sStack_5e != 0) || (sStack_56 != sStack_58)) {
          FUN_00016032(param_3._0_2_);
        }
        sStack_58 = sStack_56;
        sStack_5e = 0;
        while (sVar3 = (**(code **)(unaff_A4 + -0x7d04))(), sVar3 == 0) {
          (**(code **)(unaff_A4 + -0x7bae))();
          sVar3 = (**(code **)(unaff_A4 + -0x7d40))();
          if (sVar3 != 0) goto LAB_00016444;
          sVar3 = (**(code **)(unaff_A4 + -0x7d3a))();
          if (sVar3 != 0) {
            if (*(short *)(unaff_A4 + -0x38bc) == 1) {
              FUN_00018228();
              uStack_68 = 0xffff;
              goto LAB_00016444;
            }
            if (*(short *)(unaff_A4 + -0x38bc) == 5) {
              FUN_00018228();
              uStack_68 = 1;
              goto LAB_00016444;
            }
          }
        }
        uVar1 = (**(code **)(unaff_A4 + -0x7cfe))();
        uVar5 = (ushort)uVar1 & 0xff;
        sVar3 = (**(code **)(unaff_A4 + -0x7d10))((ushort)uVar1);
        if ((uVar5 == 0x44) || (uVar5 == 0x43)) goto LAB_00016444;
        if (uVar5 != 0x4f) break;
        sStack_56 = sStack_56 + -1;
        if ((sStack_56 < 0) || ((uVar1 & 0x30000) != 0)) {
          sStack_56 = 0;
        }
      }
      if (uVar5 != 0x4e) break;
      sStack_56 = sStack_56 + 1;
      sVar3 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
      if ((sVar3 < sStack_56) || ((uVar1 & 0x30000) != 0)) {
        sStack_56 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
      }
    }
    if (uVar5 == 0x4c) break;
    if (uVar5 == 0x4d) {
      uStack_68 = 1;
LAB_00016444:
      FUN_00016032(param_3._0_2_);
      return uStack_68;
    }
    if (uVar5 == 0x46) {
LAB_00016340:
      if (param_1[sStack_56] != '\0') {
        sStack_5a = sStack_56;
        do {
          param_1[sStack_5a] = param_1[(short)(sStack_5a + 1)];
          sStack_5a = sStack_5a + 1;
          sStack_5e = 1;
        } while (param_1[sStack_5a] != '\0');
      }
    }
    else if (uVar5 == 0x41) {
      if (sStack_56 != 0) {
        sStack_56 = sStack_56 + -1;
        goto LAB_00016340;
      }
    }
    else {
      sVar4 = (**(code **)(unaff_A4 + -0x7d10))(uVar5);
      if ((sVar4 == 0x78) && ((uVar1 & 0x800000) != 0)) {
        sStack_56 = 0;
        *param_1 = 0;
        sStack_5e = 1;
      }
      else if ((sVar3 != 0) && (sStack_56 < param_2._0_2_)) {
        for (sStack_5a = param_2._0_2_; sStack_56 < sStack_5a; sStack_5a = sStack_5a + -1) {
          param_1[sStack_5a] = param_1[(short)(sStack_5a + -1)];
        }
        param_1[param_2._0_2_] = 0;
        uStack_5b = (undefined1)sVar3;
        param_1[sStack_56] = uStack_5b;
        sStack_56 = sStack_56 + 1;
        if (param_2._0_2_ < sStack_56) {
          sStack_56 = param_2._0_2_;
        }
        sStack_5e = 1;
      }
    }
  }
  uStack_68 = 0xffff;
  goto LAB_00016444;
}


// ==== thunk_FUN_00016b60 @ 000230dc ====

void thunk_FUN_00016b60(void)

{
  int unaff_A4;
  
  load_copper_list_and_wait(*(undefined4 *)(unaff_A4 + -0x42b8));
  *(undefined4 *)(unaff_A4 + -0x38b6) = 0;
  *(undefined2 *)(unaff_A4 + -0x380e) = 0x280;
  *(undefined2 *)(unaff_A4 + -0x380c) = 200;
  *(undefined1 *)(unaff_A4 + -0x38ad) = 2;
  layout_view_bitmaps(unaff_A4 + -0x3606);
  *(undefined4 *)(unaff_A4 + -0x380a) = 0;
  *(undefined2 *)(unaff_A4 + -0x3762) = 0x280;
  *(undefined2 *)(unaff_A4 + -0x3760) = 200;
  *(undefined1 *)(unaff_A4 + -0x3801) = 2;
  layout_view_bitmaps(unaff_A4 + -0x35f8);
  flip_views_and_wait(unaff_A4 + -0x3606);
  return;
}


// ==== flip_views_and_wait @ 000230e2 ====

void flip_views_and_wait(undefined4 param_1)

{
  int unaff_A4;
  
  flip_views(param_1);
  (**(code **)(unaff_A4 + -0x7e24))();
  return;
}


// ==== thunk_FUN_00017084 @ 000230e8 ====

void thunk_FUN_00017084(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int unaff_A4;
  undefined2 auStackY_1008a [32];
  undefined2 auStackY_1004a [32732];
  undefined2 auStack_8a [32];
  undefined2 auStack_4a [32];
  short sStack_a;
  short sStack_8;
  short sStack_6;
  
  sStack_8 = 1 << (*(byte *)(*(int *)(unaff_A4 + -0x41d6) + 9) & 0x3f);
  for (sStack_6 = 0; sStack_6 < sStack_8; sStack_6 = sStack_6 + 1) {
    auStack_4a[sStack_6] =
         *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x98) + sStack_6 * 2);
  }
  if (*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) != 0) {
    for (sStack_6 = 0; sStack_6 < sStack_8; sStack_6 = sStack_6 + 1) {
      auStack_8a[sStack_6] =
           *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) + sStack_6 * 2);
    }
  }
  sStack_a = 0;
  do {
    for (sStack_6 = 0; sStack_6 < sStack_8; sStack_6 = sStack_6 + 1) {
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x98) + sStack_6 * 2) = uVar2;
      if (*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) != 0) {
        uVar2 = FUN_00016ff6();
        *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) + sStack_6 * 2) = uVar2;
      }
    }
    uVar1 = *(undefined4 *)(*(int *)(unaff_A4 + -0x41ce) + 2);
    *(undefined4 *)(*(int *)(unaff_A4 + -0x41ce) + 2) = *(undefined4 *)(unaff_A4 + -0x339a);
    *(undefined4 *)(unaff_A4 + -0x339a) = uVar1;
    build_view_copper_list(*(undefined4 *)(unaff_A4 + -0x41ce));
    flip_views(*(undefined4 *)(unaff_A4 + -0x41ce));
    sStack_a = sStack_a + 1;
  } while (sStack_a < 0x10);
  return;
}


// ==== thunk_FUN_000173b0 @ 000230ee ====

void thunk_FUN_000173b0(void)

{
  undefined2 auStack_46 [32];
  short sStack_6;
  
  sStack_6 = 0;
  do {
    auStack_46[sStack_6] = 0;
    sStack_6 = sStack_6 + 1;
  } while (sStack_6 < 0x20);
  FUN_00017084(auStack_46);
  return;
}


// ==== thunk_FUN_00018022 @ 000230f4 ====

void thunk_FUN_00018022(void)

{
  short sVar1;
  int unaff_A4;
  undefined1 auStack_44 [64];
  
  music_play_song(0x8122,2);
  FUN_00017e80();
  music_play_song(0x812b,1);
  FUN_00016ad8();
  FUN_00017422(0x8134,(short)auStack_44);
  flip_views_and_wait((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_00017084((short)unaff_A4 + -0x56b2);
  sVar1 = FUN_00016eee();
  if (sVar1 == 0) {
    FUN_00017084((short)auStack_44);
    FUN_00017422(0x8146,(short)auStack_44);
    sVar1 = FUN_00016eee();
    if (sVar1 == 0) {
      FUN_000173b0();
      flip_views_and_wait((short)*(undefined4 *)(unaff_A4 + -0x41d2));
      FUN_00017084((short)auStack_44);
      FUN_00017422(0x8158,(short)auStack_44);
      sVar1 = FUN_00016eee();
      if (sVar1 == 0) {
        FUN_000173b0();
        flip_views_and_wait((short)*(undefined4 *)(unaff_A4 + -0x41d2));
        FUN_00017084((short)auStack_44);
        FUN_00016eee();
      }
    }
  }
  FUN_000173b0();
  return;
}


// ==== thunk_FUN_0001816c @ 000230fa ====

void thunk_FUN_0001816c(void)

{
  FUN_00016e96(s_User_requested_abort__0001817e);
  return;
}


// ==== rank_select_screen @ 00023100 ====

undefined4 rank_select_screen(void)

{
  short sVar2;
  undefined4 uVar1;
  int unaff_A4;
  int iStack_50;
  short sStack_4a;
  undefined1 auStack_48 [64];
  undefined4 uStack_8;
  
  *(undefined2 *)(unaff_A4 + -0x439a) = 0;
  music_play_song(0x84f0,4);
  FUN_00016ad8();
  *(undefined2 *)(unaff_A4 + -0x42be) = 0;
  FUN_00017422(0x84f9,(short)auStack_48);
  uStack_8 = FUN_00015d4c(0x850b);
  sStack_4a = *(short *)(unaff_A4 + -0x439a);
  (**(code **)(unaff_A4 + -0x7caa))((short)*(undefined4 *)(unaff_A4 + -0x41e2));
  (**(code **)(unaff_A4 + -0x7c9e))();
  iStack_50 = (**(code **)(unaff_A4 + -0x7d2e))((short)uStack_8);
  (**(code **)(unaff_A4 + -0x7cce))((short)iStack_50,*(undefined2 *)(iStack_50 + 10));
  flip_views_and_wait((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_00017084((short)auStack_48);
  copy_view((short)*(undefined4 *)(unaff_A4 + -0x41ce),(short)*(undefined4 *)(unaff_A4 + -0x41d2));
LAB_00018302:
  do {
    sVar2 = FUN_00018194();
    if (sVar2 != 0) {
      if (sVar2 != 1000) {
        *(short *)(unaff_A4 + -0x439a) = sVar2 + *(short *)(unaff_A4 + -0x439a);
        if (*(short *)(unaff_A4 + -0x439a) < 0) {
          *(undefined2 *)(unaff_A4 + -0x439a) = 7;
        }
        if (7 < *(short *)(unaff_A4 + -0x439a)) {
          *(undefined2 *)(unaff_A4 + -0x439a) = 0;
        }
        if (*(short *)(unaff_A4 + -0x439a) != sStack_4a) {
          (**(code **)(unaff_A4 + -0x7caa))((short)*(undefined4 *)(unaff_A4 + -0x41e2));
          (**(code **)(unaff_A4 + -0x7cce))((short)iStack_50,*(undefined2 *)(iStack_50 + 10));
          iStack_50 = (**(code **)(unaff_A4 + -0x7d2e))((short)uStack_8);
          (**(code **)(unaff_A4 + -0x7cce))((short)iStack_50,*(undefined2 *)(iStack_50 + 10));
          flip_views_and_wait((short)*(undefined4 *)(unaff_A4 + -0x41d2));
          copy_view((short)*(undefined4 *)(unaff_A4 + -0x41ce),
                    (short)*(undefined4 *)(unaff_A4 + -0x41d2));
          sStack_4a = *(short *)(unaff_A4 + -0x439a);
          FUN_00018228();
        }
        goto LAB_00018302;
      }
      *(undefined2 *)(unaff_A4 + -0x42b2) = 1;
    }
    if (*(short *)(unaff_A4 + -0x439a) != 7) {
      (**(code **)(unaff_A4 + -0x7cec))((short)uStack_8);
      FUN_000173b0();
      if ((*(short *)(unaff_A4 + -0x42b2) == 0) && (*(int *)(unaff_A4 + -0x4078) != 0)) {
        uVar1 = (**(code **)(unaff_A4 + -0x7cf8))(5000);
        *(undefined4 *)(unaff_A4 + -0x42b0) = uVar1;
        *(undefined2 *)(unaff_A4 + -0x42b2) = 2;
      }
      if (*(short *)(unaff_A4 + -0x42b2) == 1) {
        uVar1 = FUN_00015d3e(0x8521);
        *(undefined4 *)(unaff_A4 + -0x42b0) = uVar1;
      }
      *(undefined2 *)(unaff_A4 + -0x42ac) = 0;
      if (*(int *)(unaff_A4 + -0x42b0) == 0) {
        *(undefined2 *)(unaff_A4 + -0x42b2) = 0;
      }
      if (*(short *)(unaff_A4 + -0x42b2) != 0) {
        (**(code **)(unaff_A4 + -0x7e7e))();
        (**(code **)(unaff_A4 + -0x7d46))();
      }
      *(undefined2 *)(unaff_A4 + -0x5aa6) = *(undefined2 *)(unaff_A4 + -0x439a);
      *(undefined2 *)(unaff_A4 + -0x5c40) = *(undefined2 *)(unaff_A4 + -0x439a);
      if (*(short *)(unaff_A4 + -0x42b2) == 1) {
        sVar2 = *(short *)(unaff_A4 + -0x42ac);
        *(short *)(unaff_A4 + -0x42ac) = *(short *)(unaff_A4 + -0x42ac) + 1;
        *(short *)(unaff_A4 + -0x5c40) = (short)*(char *)(*(int *)(unaff_A4 + -0x42b0) + (int)sVar2)
        ;
      }
      if (*(short *)(unaff_A4 + -0x42b2) == 2) {
        sVar2 = *(short *)(unaff_A4 + -0x42ac);
        *(short *)(unaff_A4 + -0x42ac) = *(short *)(unaff_A4 + -0x42ac) + 1;
        *(undefined1 *)(*(int *)(unaff_A4 + -0x42b0) + (int)sVar2) =
             *(undefined1 *)(unaff_A4 + -0x5c3f);
      }
      *(undefined2 *)(unaff_A4 + -0x5c3e) = 1;
      goto LAB_000184d6;
    }
    sVar2 = load_save_game_dialog();
    if (sVar2 == 0) {
      *(undefined2 *)(unaff_A4 + -0x42be) = 1;
      (**(code **)(unaff_A4 + -0x7cec))((short)uStack_8);
      FUN_000173b0();
LAB_000184d6:
      music_stop_unload();
      return *(undefined4 *)(unaff_A4 + -0x79ae + *(short *)(unaff_A4 + -0x5aa6) * 4);
    }
    FUN_00016a98((short)*(undefined4 *)(unaff_A4 + -0x41d2));
    copy_view((short)*(undefined4 *)(unaff_A4 + -0x41ce),(short)*(undefined4 *)(unaff_A4 + -0x41d2))
    ;
    build_view_copper_list((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  } while( true );
}


// ==== finish_demo_recording @ 00023106 ====

void finish_demo_recording(void)

{
  int unaff_A4;
  
  if ((*(short *)(unaff_A4 + -0x42b2) == 2) && (*(int *)(unaff_A4 + -0x4078) != 0)) {
    *(undefined1 *)(*(int *)(unaff_A4 + -0x42b0) + (int)*(short *)(unaff_A4 + -0x42ac)) = 0xff;
    (**(code **)(unaff_A4 + -0x7d64))
              (*(undefined4 *)(unaff_A4 + -0x4078),*(undefined4 *)(unaff_A4 + -0x42b0),5000);
  }
  FUN_000124dc(unaff_A4 + -0x42b0);
  *(undefined2 *)(unaff_A4 + -0x42b2) = 0;
  return;
}


// ==== mission_briefing_screen @ 0002310c ====

undefined4 mission_briefing_screen(void)

{
  int iVar1;
  uint uVar2;
  char cVar4;
  short sVar3;
  int unaff_A4;
  undefined2 uVar5;
  short sStack_84;
  undefined1 auStack_76 [50];
  undefined1 auStack_44 [64];
  
  FUN_00016b04();
  iVar1 = (**(code **)(unaff_A4 + -0x7d34))((short)*(undefined4 *)(unaff_A4 + -0x69cc),0x6e6b);
  uVar5 = (undefined2)*(undefined4 *)(unaff_A4 + -0x41e2);
  (**(code **)(unaff_A4 + -0x7caa))(uVar5);
  (**(code **)(unaff_A4 + -0x7c9e))();
  (**(code **)(unaff_A4 + -0x7c5c))((short)unaff_A4 + -0x56d2,(short)auStack_44);
  (**(code **)(unaff_A4 + -0x7cda))((short)iVar1,0,0x65 - (*(ushort *)(iVar1 + 2) >> 1));
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x128,0x3d);
  FUN_00018570((short)*(undefined4 *)(unaff_A4 + -0x56ee + *(short *)(unaff_A4 + -0x5c40) * 4));
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x154,0x49);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_76,0x8764);
  FUN_00018570((short)auStack_76);
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x154,0x77);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_76,0x8767);
  FUN_00018570((short)auStack_76);
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x154,0x83);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_76,0x876a);
  FUN_00018570((short)auStack_76);
  flip_views_and_wait((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_00017084((short)auStack_44);
  (**(code **)(unaff_A4 + -0x7bae))();
  sStack_84 = 1;
  do {
    if ((0xef < sStack_84) || (sVar3 = (**(code **)(unaff_A4 + -0x7d40))(), sVar3 != 0)) {
      FUN_000173b0();
      return 0;
    }
    (**(code **)(unaff_A4 + -0x7bae))();
    sVar3 = (**(code **)(unaff_A4 + -0x7d04))();
    if (sVar3 != 0) {
      uVar2 = (**(code **)(unaff_A4 + -0x7cfe))();
      if (((uVar2 & 0x80000) != 0) &&
         (cVar4 = (**(code **)(unaff_A4 + -0x7d10))((short)uVar2), cVar4 == 'r')) {
        FUN_000173b0();
        return 1;
      }
    }
    sStack_84 = sStack_84 + 1;
  } while( true );
}


// ==== update_waterline_split @ 00023112 ====

void update_waterline_split(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  uVar1 = *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d2) + 2) + 2);
  *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d2) + 2) + 2) =
       *(undefined2 *)(unaff_A4 + -0x3392);
  copper_wait(*(undefined4 *)(*(int *)(unaff_A4 + -0x41d2) + 2));
  *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d2) + 2) + 2) = uVar1;
  return;
}


// ==== setup_level_display @ 00023118 ====

void setup_level_display(void)

{
  int unaff_A4;
  undefined2 uStack_6;
  
  load_copper_list_and_wait(*(undefined4 *)(unaff_A4 + -0x42b8));
  init_game_display();
  load_iff_into_viewport(*(undefined4 *)(unaff_A4 + -0x38ba),**(undefined4 **)(unaff_A4 + -0x41de));
  (**(code **)(unaff_A4 + -0x7cec))(*(undefined4 *)(unaff_A4 + -0x38ba));
  uStack_6 = 0;
  do {
    *(undefined2 *)(unaff_A4 + -0x3566 + uStack_6 * 2) =
         *(undefined2 *)(*(int *)(**(int **)(unaff_A4 + -0x41de) + 0x98) + uStack_6 * 2);
    *(undefined2 *)(unaff_A4 + -0x3526 + uStack_6 * 2) =
         *(undefined2 *)(*(int *)(**(int **)(unaff_A4 + -0x41de) + 0x98) + uStack_6 * 2);
    uStack_6 = uStack_6 + 1;
  } while (uStack_6 < 0x20);
  *(undefined4 *)(unaff_A4 + -0x5848) = 0;
  *(undefined2 *)(unaff_A4 + -0x5a36) = 0;
  FUN_00015d3e(*(undefined4 *)(unaff_A4 + -0x570e + *(short *)(unaff_A4 + -0x5c6e) * 4));
  cmap_file_to_palette
            (*(undefined4 *)(unaff_A4 + -0x3384),
             *(undefined4 *)(*(int *)(unaff_A4 + -0x41de) + 0x98));
  (**(code **)(unaff_A4 + -0x7cec))(*(undefined4 *)(unaff_A4 + -0x3384));
  FUN_00015d3e(*(undefined4 *)(unaff_A4 + -0x56fe + *(short *)(unaff_A4 + -0x5c6e) * 4));
  cmap_file_to_palette
            (*(undefined4 *)(unaff_A4 + -0x3384),
             *(undefined4 *)(*(int *)(unaff_A4 + -0x41de) + 0x9c));
  (**(code **)(unaff_A4 + -0x7cec))(*(undefined4 *)(unaff_A4 + -0x3384));
  *(undefined2 *)(*(int *)(*(int *)**(undefined4 **)(unaff_A4 + -0x41de) + 0x98) + 2) = 0x777;
  load_copper_list_and_wait(*(undefined4 *)(unaff_A4 + -0x42b8));
  copy_view(*(undefined4 *)(unaff_A4 + -0x41d2),*(undefined4 *)(unaff_A4 + -0x41ce));
  build_view_copper_list(*(undefined4 *)(unaff_A4 + -0x41d2));
  build_view_copper_list(*(undefined4 *)(unaff_A4 + -0x41ce));
  copper_add_ticker_gradient(*(undefined4 *)(*(int *)(unaff_A4 + -0x41d2) + 2));
  copper_add_ticker_gradient(*(undefined4 *)(*(int *)(unaff_A4 + -0x41ce) + 2));
  build_enemy_plane_frame_tables();
  return;
}


// ==== high_score_screen @ 0002311e ====

void high_score_screen(void)

{
  int unaff_A4;
  undefined1 auStack_21e [410];
  undefined1 auStack_84 [64];
  undefined1 auStack_44 [64];
  
  *(undefined1 **)(unaff_A4 + -0x3224) = auStack_21e;
  music_play_song(0x9928,0);
  high_score_check_and_entry();
  FUN_00016d7a();
  *(int *)(unaff_A4 + -0x41d2) = unaff_A4 + -0x3606;
  *(undefined4 *)(unaff_A4 + -0x41de) = **(undefined4 **)(*(int *)(unaff_A4 + -0x41d2) + 6);
  *(int *)(unaff_A4 + -0x41e2) = *(int *)(unaff_A4 + -0x41de) + 0x2c;
  *(int *)(unaff_A4 + -0x41ca) = *(int *)(unaff_A4 + -0x41de) + 4;
  FUN_00017422(0x9931,(short)auStack_84);
  (**(code **)(unaff_A4 + -0x7caa))((short)*(undefined4 *)(unaff_A4 + -0x41e2));
  (**(code **)(unaff_A4 + -0x7c9e))();
  draw_high_score_table();
  *(undefined4 *)(unaff_A4 + -0x41de) = *(undefined4 *)(*(int *)(unaff_A4 + -0x41d2) + 6);
  *(int *)(unaff_A4 + -0x41e2) = *(int *)(unaff_A4 + -0x41de) + 0x2c;
  *(int *)(unaff_A4 + -0x41ca) = *(int *)(unaff_A4 + -0x41de) + 4;
  FUN_00017422(0x9944,(short)auStack_44);
  flip_views_and_wait((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_000171f2((short)auStack_44,(short)auStack_84);
  FUN_00016eee();
  FUN_000173e6();
  return;
}


// ==== wait_next_vbl @ 00023124 ====

void wait_next_vbl(void)

{
  int unaff_A4;
  
  *(undefined1 *)(unaff_A4 + -0x5a40) = 0;
  do {
  } while (*(char *)(unaff_A4 + -0x5a40) == '\0');
  return;
}


// ==== wait_vbl_flag @ 0002312a ====

void wait_vbl_flag(void)

{
  int unaff_A4;
  
  do {
  } while (*(char *)(unaff_A4 + -0x5a40) == '\0');
  *(undefined1 *)(unaff_A4 + -0x5a40) = 0;
  return;
}


// ==== thunk_FUN_0001aa50 @ 00023130 ====

void thunk_FUN_0001aa50(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x321c) = 1;
  *(undefined2 *)(unaff_A4 + -0x321a) = 0;
  return;
}


// ==== player_gun_vs_enemy_planes @ 00023136 ====

void player_gun_vs_enemy_planes(void)

{
  short *psVar1;
  byte *pbVar2;
  short sVar3;
  int unaff_A4;
  int iVar4;
  undefined2 uStack_10;
  undefined2 uStack_e;
  
  if (*(short *)(unaff_A4 + -0x5c94) != 0) {
    uStack_e = 0;
    *(int *)(unaff_A4 + -0x320e) = unaff_A4 + -0x5dd4;
    while (uStack_e < 4) {
      if (*(short *)(*(int *)(unaff_A4 + -0x320e) + 4) == 3) {
        uStack_10 = *(short *)(*(int *)(unaff_A4 + -0x3212) + 2) -
                    *(short *)(*(int *)(unaff_A4 + -0x320e) + 0x20);
        if (uStack_10 < 0) {
          uStack_10 = -uStack_10;
        }
        sVar3 = **(short **)(unaff_A4 + -0x3212) - *(short *)(*(int *)(unaff_A4 + -0x320e) + 0x26);
        if (sVar3 < 0) {
          sVar3 = -sVar3;
        }
        if (((uStack_10 < 0xa0) && (sVar3 < 0x14)) && (*(short *)(unaff_A4 + -0x5bfc) == 0)) {
          *(undefined2 *)(*(int *)(unaff_A4 + -0x320e) + 6) = 1;
          iVar4 = *(int *)(unaff_A4 + -0x320e);
          psVar1 = (short *)(iVar4 + 10);
          *psVar1 = *psVar1 + -1;
          if (*(short *)(iVar4 + 10) < 1) {
            FUN_0001cae0(6,CONCAT22(*(short *)(*(int *)(unaff_A4 + -0x320e) + 0x20) + -0x10,
                                    *(short *)(*(int *)(unaff_A4 + -0x320e) + 0x26) + 10));
            psVar1 = (short *)(*(int *)(unaff_A4 + -0x320e) + 8);
            *psVar1 = *psVar1 + -8;
            if (*(short *)(*(int *)(unaff_A4 + -0x320e) + 8) < 0x60) {
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x15e;
              **(undefined2 **)(unaff_A4 + -0x320e) = 4;
              *(undefined2 *)(*(int *)(unaff_A4 + -0x320e) + 0x24) = 0xfffd;
              *(undefined2 *)(*(int *)(unaff_A4 + -0x320e) + 0x16) = 0;
              pbVar2 = (byte *)(*(int *)(unaff_A4 + -0x320e) + 3);
              *pbVar2 = *pbVar2 & 0xf7;
              enemy_plane_set_sprite(*(undefined4 *)(unaff_A4 + -0x320e));
            }
            iVar4 = *(int *)(unaff_A4 + -0x320e);
            sVar3 = rand_mod();
            *(short *)(iVar4 + 10) = sVar3 + 6;
          }
        }
      }
      uStack_e = uStack_e + 1;
      *(int *)(unaff_A4 + -0x320e) = *(int *)(unaff_A4 + -0x320e) + 0x34;
    }
  }
  return;
}


// ==== player_reset @ 0002313c ====

void player_reset(void)

{
  short sVar2;
  undefined4 uVar1;
  int unaff_A4;
  int iVar3;
  
  *(int *)(unaff_A4 + -0x3212) = unaff_A4 + -0x5f86;
  init_carrier_deck_bounds();
  **(undefined2 **)(unaff_A4 + -0x3212) = 0;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0x16) = 0;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0x18) = 0;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 1;
  iVar3 = *(int *)(unaff_A4 + -0x3212);
  sVar2 = rand_mod();
  *(short *)(iVar3 + 0x10) = sVar2 + 6;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0x12) = 0x80;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xe) = 0xc0;
  uVar1 = select_hellcat_frame();
  *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8) = uVar1;
  uVar1 = FUN_0001cb30((short)*(undefined4 *)(unaff_A4 + -0x69c0),
                       *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8));
  *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 4) = uVar1;
  uVar1 = FUN_0001cb30((short)*(undefined4 *)(unaff_A4 + -0x69bc),
                       *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8));
  *(undefined4 *)(unaff_A4 + -0x5be0) = uVar1;
  *(undefined2 *)(unaff_A4 + -0x5bfc) = 0;
  *(undefined2 *)(unaff_A4 + -0x5f6a) = 0x546;
  *(undefined2 *)(unaff_A4 + -0x5bea) = 0;
  *(undefined2 *)(unaff_A4 + -0x5bf4) = 5;
  *(undefined2 *)(unaff_A4 + -0x5cb4) = 5;
  *(undefined2 *)(unaff_A4 + -0x5562) = 0;
  *(undefined2 *)(unaff_A4 + -0x3e96) = 0x1c;
  *(undefined2 *)(unaff_A4 + -0x3cb0) = *(undefined2 *)(unaff_A4 + -0x3e96);
  return;
}


// ==== engine_sound_off @ 00023142 ====

void engine_sound_off(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x5bd2) = 0;
  *(undefined2 *)(unaff_A4 + -0x5bd6) = 0;
  return;
}


// ==== engine_sound_start @ 00023148 ====

void engine_sound_start(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x5bd2) = 0x28;
  *(undefined2 *)(unaff_A4 + -0x5bd6) = 0x28;
  *(undefined2 *)(unaff_A4 + -0x5bd0) = 0x328;
  *(undefined2 *)(unaff_A4 + -0x5bd4) = 0x328;
  *(undefined2 *)(unaff_A4 + -0x3216) = 0;
  return;
}


// ==== player_update @ 0002314e ====

void player_update(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  int unaff_A4;
  undefined2 uStack_1a;
  undefined2 uVar4;
  
  *(undefined2 *)(unaff_A4 + -0x5bee) = 100;
  player_fire_input();
  update_bomber_spawn_timer();
  if (*(short *)(unaff_A4 + -0x5c9a) == 0) {
    if (*(short *)(unaff_A4 + -0x5bea) == 0) {
      *(undefined2 *)(unaff_A4 + -0x4374) = 0;
    }
    switch(*(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc)) {
    case 0:
      if ((*(short *)(*(int *)(unaff_A4 + -0x3212) + 0x12) < 0x60) ||
         (*(short *)(*(int *)(unaff_A4 + -0x3212) + 0xe) < 0)) {
        *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 4;
        *(short *)(unaff_A4 + -0x5bea) = *(short *)(*(int *)(unaff_A4 + -0x3212) + 0x16) * 100;
        player_crash_update();
      }
      else if (**(short **)(unaff_A4 + -0x3212) < -6) {
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 6;
        *(undefined2 *)(unaff_A4 + -0x5556) = 0;
        *(undefined2 *)(unaff_A4 + -0x5558) = 0;
        *(undefined2 *)(unaff_A4 + -0x555a) = 0;
        *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
      }
      else {
        player_flight_controls();
        FUN_0001b9f0();
        player_flight_physics();
        player_ground_check();
        if (**(short **)(unaff_A4 + -0x3212) < 0x51) {
          *(undefined1 *)(unaff_A4 + -0x5c9f) = 2;
        }
        else {
          *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
        }
        deck_crew_signal();
      }
      break;
    case 1:
      deck_throttle();
      deck_move();
      deck_height_or_takeoff();
      arrester_wire_check();
      deck_crew_signal();
      break;
    default:
      uStack_1a = (undefined2)((uint)*(undefined4 *)(unaff_A4 + -0x3212) >> 0x10);
      uVar4 = (undefined2)*(undefined4 *)(unaff_A4 + -0x3212);
      sVar1 = wheel_clearance();
      uVar2 = map_ptr_from_x();
      sVar3 = object_height(uVar2);
      *(short *)CONCAT22(uStack_1a,uVar4) = sVar3 + sVar1;
      if (*(short *)(*(int *)(unaff_A4 + -0x320a) + 2) == 0) {
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 1;
      }
      break;
    case 4:
      *(undefined2 *)(unaff_A4 + -0x5bd6) = 0x19;
      *(undefined2 *)(unaff_A4 + -0x5bd4) = 0x3c0;
      *(undefined2 *)(unaff_A4 + -0x3216) = 0;
      *(undefined2 *)(unaff_A4 + -0x5c94) = 0;
      *(undefined2 *)(unaff_A4 + -0x5bf6) = 0;
      map_ptr_from_x();
      *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
      *(undefined2 *)(unaff_A4 + -0x5560) = 0xffff;
      player_crash_update();
      break;
    case 6:
      *(undefined2 *)(unaff_A4 + -0x5bd6) = 0;
      *(short *)(unaff_A4 + -0x555a) = *(short *)(unaff_A4 + -0x555a) + 1;
      if (2 < *(short *)(unaff_A4 + -0x555a)) {
        *(undefined2 *)(unaff_A4 + -0x555a) = 0;
        **(short **)(unaff_A4 + -0x3212) = **(short **)(unaff_A4 + -0x3212) + -1;
      }
      *(short *)(unaff_A4 + -0x5bfc) = *(short *)(unaff_A4 + -0x5bfc) + -0xfa;
      if (*(short *)(unaff_A4 + -0x5bfc) < -0x1194) {
        *(undefined2 *)(unaff_A4 + -0x5bfc) = 0xee6c;
      }
      wreck_explosions();
      respawn_timer();
      break;
    case 7:
      *(undefined2 *)(unaff_A4 + -0x5bd6) = 0x28;
      *(undefined2 *)(unaff_A4 + -0x5bd4) = 0x328;
      uStack_1a = (undefined2)((uint)*(undefined4 *)(unaff_A4 + -0x3212) >> 0x10);
      uVar4 = (undefined2)*(undefined4 *)(unaff_A4 + -0x3212);
      sVar1 = wheel_clearance();
      uVar2 = map_ptr_from_x();
      sVar3 = object_height(uVar2);
      *(short *)CONCAT22(uStack_1a,uVar4) = sVar3 + sVar1;
      *(undefined2 *)(unaff_A4 + -0x5bfc) = 0;
      *(undefined2 *)(unaff_A4 + -0x5bf6) = 0;
      *(undefined2 *)(unaff_A4 + -0x4374) = 0;
      *(short *)(unaff_A4 + -0x5bea) = *(short *)(unaff_A4 + -0x5bea) + -0x6e;
      if (*(short *)(unaff_A4 + -0x5bea) < 0) {
        *(undefined2 *)(unaff_A4 + -0x5bea) = 0;
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 1;
        *(undefined2 *)(unaff_A4 + -0x5560) = 0xffff;
      }
      deck_move();
      break;
    case 8:
      *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8) = 0x68637235;
      if (*(short *)(*(int *)(unaff_A4 + -0x3212) + 0x14) == -1) {
        *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8) = 0x68637266;
      }
      *(undefined2 *)(unaff_A4 + -0x5a6c) = 0;
      uVar2 = map_ptr_from_x();
      sVar1 = map_cell_is_ship(uVar2);
      if (sVar1 == 0) {
        uVar2 = wheel_clearance();
        **(undefined2 **)(unaff_A4 + -0x3212) = uVar2;
      }
      else {
        uStack_1a = (undefined2)((uint)*(undefined4 *)(unaff_A4 + -0x3212) >> 0x10);
        uVar4 = (undefined2)*(undefined4 *)(unaff_A4 + -0x3212);
        sVar1 = wheel_clearance();
        sVar3 = object_height(uVar2);
        *(short *)CONCAT22(uStack_1a,uVar4) = sVar3 + sVar1;
      }
      *(short *)(unaff_A4 + -0x437a) = *(short *)(unaff_A4 + -0x437a) + 1;
      if ((*(ushort *)(unaff_A4 + -0x437a) & 3) == 0) {
        FUN_0001cae0(6,**(short **)(unaff_A4 + -0x3212) + 0xb);
      }
      wreck_explosions();
      respawn_timer();
      break;
    case 9:
    }
    update_gear_target();
    player_select_frames();
  }
  else {
    *(undefined2 *)(unaff_A4 + -0x3214) = 0;
    *(undefined2 *)(unaff_A4 + -0x5bea) = 0;
  }
  *(undefined2 *)(unaff_A4 + -0x5c4e) = 8;
  if (0xba < **(short **)(unaff_A4 + -0x3212)) {
    *(undefined2 *)(unaff_A4 + -0x5c4e) = 1;
  }
  return;
}


// ==== fire_button_debounce @ 00023154 ====

void fire_button_debounce(void)

{
  short sVar1;
  int unaff_A4;
  
  *(int *)(unaff_A4 + -0x436c) = *(int *)(unaff_A4 + -0x436c) + 1;
  sVar1 = (**(code **)(unaff_A4 + -0x7d40))();
  if ((sVar1 != 0) && (*(short *)(unaff_A4 + -0x4372) == 0)) {
    *(undefined4 *)(unaff_A4 + -0x4370) = *(undefined4 *)(unaff_A4 + -0x436c);
  }
  if (*(int *)(unaff_A4 + -0x436c) < *(int *)(unaff_A4 + -0x4370) + 10) {
    if ((sVar1 == 0) && (*(short *)(unaff_A4 + -0x4372) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x3202) = 1;
    }
  }
  else if (sVar1 != 0) {
    *(undefined2 *)(unaff_A4 + -0x3204) = 1;
  }
  if (sVar1 == 0) {
    *(undefined4 *)(unaff_A4 + -0x4370) = 0;
  }
  *(short *)(unaff_A4 + -0x4372) = sVar1;
  return;
}


// ==== build_input_word @ 0002315a ====

void build_input_word(void)

{
  ushort uVar1;
  int unaff_A4;
  
  uVar1 = FUN_0001cb20();
  *(undefined2 *)(unaff_A4 + -0x3c98) = 0;
  if (*(short *)(unaff_A4 + -0x3202) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 0x20;
    *(undefined2 *)(unaff_A4 + -0x3202) = 0;
    *(undefined2 *)(unaff_A4 + -0x3204) = 0;
  }
  if (*(short *)(unaff_A4 + -0x3204) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 0x10;
    *(undefined2 *)(unaff_A4 + -0x3204) = 0;
  }
  if ((uVar1 & 1) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 1;
  }
  if ((uVar1 & 2) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 2;
  }
  if ((uVar1 & 4) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 8;
  }
  if ((uVar1 & 8) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 4;
  }
  return;
}


// ==== ship_num_from_map_ptr @ 00023160 ====

undefined4 ship_num_from_map_ptr(undefined4 param_1)

{
  short sVar1;
  int unaff_A4;
  short sStack_8;
  
  sVar1 = map_cell_is_ship(param_1);
  if (sVar1 == 0) {
    (**(code **)(unaff_A4 + -0x7c7a))(s_Not_over_a_ship_in_ShipNum__0001cc76);
  }
  else {
    sVar1 = (short)param_1 - (short)*(undefined4 *)(unaff_A4 + -0x69d6);
    sStack_8 = 0;
    do {
      if ((**(short **)(unaff_A4 + -0x5aa4 + sStack_8 * 4) <= sVar1) &&
         (sVar1 <= *(short *)(*(int *)(unaff_A4 + -0x5aa4 + sStack_8 * 4) + 2))) {
        return CONCAT22((short)((uint)(sStack_8 * 4) >> 0x10),sStack_8);
      }
      sStack_8 = sStack_8 + 1;
    } while (sStack_8 < 5);
    (**(code **)(unaff_A4 + -0x7c7a))(s_COULDN_T_FIND_A_SHIP_in_ShipNum__0001cc93);
  }
  return 1;
}


// ==== thunk_FUN_0001ccb6 @ 00023166 ====

void thunk_FUN_0001ccb6(undefined4 param_1)

{
  int iVar1;
  int unaff_A4;
  
  iVar1 = FUN_00022b7c(0);
  if (((iVar1 < 400000) && (param_1._0_2_ != 0)) &&
     (*(int *)(*(int *)(unaff_A4 + -0x40d8) + 0x34) != 0)) {
    *(undefined2 *)(unaff_A4 + -0x41e4) = 1;
    FUN_00022f1c(*(undefined4 *)(*(int *)(unaff_A4 + -0x40d8) + 0x34));
  }
  FUN_00022f28();
  return;
}


// ==== keyboard_commands @ 0002316c ====

/* WARNING: Control flow encountered unimplemented instructions */

void keyboard_commands(void)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  char cVar8;
  short sVar6;
  undefined2 uVar7;
  undefined4 uVar4;
  int iVar5;
  ushort *puVar9;
  int unaff_A4;
  undefined1 uVar10;
  
  *(undefined4 *)(unaff_A4 + -0x40a2) = 0;
  uVar10 = 1;
LAB_0001ccfa:
  while( true ) {
    (**(code **)(unaff_A4 + -0x7d04))();
    if ((bool)uVar10) {
      return;
    }
    uVar3 = (**(code **)(unaff_A4 + -0x7cfe))();
    *(uint *)(unaff_A4 + -0x40a2) = uVar3 & 0x7fffffff;
    cVar8 = (**(code **)(unaff_A4 + -0x7d10))((short)uVar3);
    if ((*(ushort *)(unaff_A4 + -0x40a2) & 8) == 0) break;
    if (cVar8 == 'r') {
      *(undefined4 *)(unaff_A4 + -0x5848) = 0;
      clear_ticker();
      uVar10 = 0;
      FUN_000173e6();
      *(undefined1 *)(unaff_A4 + -0x5a3e) = 0xff;
      *(undefined1 *)(unaff_A4 + -0x5c3c) = 0xff;
    }
    else if (cVar8 == 's') {
      bVar1 = ~*(byte *)(unaff_A4 + -0x5b07);
      *(byte *)(unaff_A4 + -0x5b07) = bVar1;
      uVar10 = bVar1 == 0;
      if (!(bool)uVar10) {
        (**(code **)(unaff_A4 + -0x7f9e))();
      }
    }
    else if (cVar8 == 'f') {
      bVar1 = ~*(byte *)(unaff_A4 + -0x5b08);
      *(byte *)(unaff_A4 + -0x5b08) = bVar1;
      uVar10 = bVar1 == 0;
    }
    else if (cVar8 == 'g') {
      uVar10 = 0;
      if (*(short *)(unaff_A4 + -0x5f7a) == 1) {
        (**(code **)(unaff_A4 + -0x7f9e))();
        uVar10 = 0;
        load_save_game_dialog();
        rebuild_game_display();
        (**(code **)(unaff_A4 + -0x7fb6))();
      }
    }
    else if (cVar8 == 'l') {
      uVar10 = 0;
      if (*(short *)(unaff_A4 + -0x42b2) == 0) {
        (**(code **)(unaff_A4 + -0x7f9e))();
        (**(code **)(unaff_A4 + -0x7f56))();
        (**(code **)(unaff_A4 + -0x7f5c))();
        (**(code **)(unaff_A4 + -0x7fc2))();
        *(undefined2 *)(unaff_A4 + -0x42be) = 0;
        sVar6 = load_save_game_dialog();
        uVar10 = sVar6 == 0;
        if ((bool)uVar10) {
          *(undefined2 *)(unaff_A4 + -0x42be) = 1;
          load_dash_shapes();
          (**(code **)(unaff_A4 + -0x7e42))();
          (**(code **)(unaff_A4 + -0x7d8e))();
          (**(code **)(unaff_A4 + -0x7e36))();
          (**(code **)(unaff_A4 + -0x7f68))();
          FUN_0001535a();
          (**(code **)(unaff_A4 + -0x7f62))();
          *(undefined1 *)(unaff_A4 + -0x69b0) = 0;
          *(undefined2 *)(unaff_A4 + -0x42be) = 0;
          uVar10 = 1;
          (**(code **)(unaff_A4 + -0x7fbc))();
          (**(code **)(unaff_A4 + -0x7fb6))();
        }
        else {
          load_dash_shapes();
          (**(code **)(unaff_A4 + -0x7f62))();
          rebuild_game_display();
          (**(code **)(unaff_A4 + -0x7fb6))();
        }
      }
    }
    else {
      if (cVar8 == 'b') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
        halt_unimplemented();
      }
      if (cVar8 == 'c') {
        uVar10 = 0;
        (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x48))();
      }
      else {
        if (cVar8 != 'v') break;
        uVar10 = *(short *)(unaff_A4 + -0x321c) == 0;
        (**(code **)(unaff_A4 + -0x7f1a))(*(undefined2 *)(unaff_A4 + -0x321a));
        (**(code **)(unaff_A4 + -0x7ea8))();
      }
    }
  }
  if (cVar8 == '\x1b') {
    bVar1 = ~*(byte *)(unaff_A4 + -0x5aa8);
    *(byte *)(unaff_A4 + -0x5aa8) = bVar1;
    uVar10 = bVar1 == 0;
    if (!(bool)uVar10) {
      (**(code **)(unaff_A4 + -0x7f9e))();
    }
    goto LAB_0001ccfa;
  }
  if (cVar8 == 'o') {
    if (*(short *)(unaff_A4 + -0x50e6) == 1) {
      sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
      *(short *)(unaff_A4 + -0x50e6) = sVar6;
      uVar10 = sVar6 == 0;
      goto LAB_0001ccfa;
    }
  }
  else if (cVar8 == 'l') {
    if (*(short *)(unaff_A4 + -0x50e6) == 2) {
      sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
      *(short *)(unaff_A4 + -0x50e6) = sVar6;
      uVar10 = sVar6 == 0;
      goto LAB_0001ccfa;
    }
  }
  else {
    if (cVar8 != 'n') {
      if (cVar8 == 'i') {
        uVar10 = 1;
        if (*(short *)(unaff_A4 + -0x50e6) == 0) goto LAB_0001ccfa;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          sVar6 = *(short *)(unaff_A4 + -0x50e8) + 0x32;
          *(short *)(unaff_A4 + -0x50e8) = sVar6;
          uVar10 = sVar6 == 0;
          goto LAB_0001ccfa;
        }
        if (*(short *)(unaff_A4 + -0x50e6) == 3) {
          sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
          *(short *)(unaff_A4 + -0x50e6) = sVar6;
          uVar10 = sVar6 == 0;
          goto LAB_0001ccfa;
        }
        *(undefined2 *)(unaff_A4 + -0x50e6) = 0;
      }
      if (cVar8 == 'k') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          sVar6 = *(short *)(unaff_A4 + -0x50e8) + -0x32;
          *(short *)(unaff_A4 + -0x50e8) = sVar6;
          uVar10 = sVar6 == 0;
        }
      }
      else if (cVar8 == 'f') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          *(undefined2 *)(unaff_A4 + -0x5f78) = 0x80;
          uVar10 = 0;
        }
      }
      else if (cVar8 == 'p') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          cVar8 = *(char *)(unaff_A4 + -0x5ca2) + '\x01';
          *(char *)(unaff_A4 + -0x5ca2) = cVar8;
          uVar10 = cVar8 == '\0';
        }
      }
      else if (*(char *)(unaff_A4 + -0x409f) == 'Y') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          *(undefined4 *)(unaff_A4 + -0x5848) = 0;
          uVar10 = 1;
        }
      }
      else if (cVar8 == ' ') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          iVar5 = *(int *)(unaff_A4 + -0x408a);
          uVar7 = (**(code **)(iVar5 + -0xd8))();
          uVar7 = (**(code **)(iVar5 + -0xd8))(uVar7);
          uVar4 = (**(code **)(iVar5 + -0xd8))(uVar7);
          iVar5 = (**(code **)(iVar5 + -0xd8))(uVar4);
          uVar10 = iVar5 == 0;
          (**(code **)(unaff_A4 + -0x7f1a))(iVar5);
          (**(code **)(unaff_A4 + -0x7ea8))();
        }
      }
      else if (*(char *)(unaff_A4 + -0x409f) == '_') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          sVar6 = 0;
          puVar9 = (ushort *)(unaff_A4 + -0x5bc6);
          while (*puVar9 <= *(ushort *)(unaff_A4 + -0x41a2) >> 2) {
            sVar6 = sVar6 + 1;
            puVar9 = puVar9 + 1;
          }
          uVar10 = sVar6 == 0;
          (**(code **)(unaff_A4 + -0x7f1a))();
          (**(code **)(unaff_A4 + -0x7ea8))();
        }
      }
      else if (cVar8 == 'q') {
        uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
        if ((bool)uVar10) {
          *(undefined1 *)(unaff_A4 + -0x407e) = 0xff;
          *(undefined1 *)(unaff_A4 + -0x5c3c) = 0xff;
        }
      }
      else if (cVar8 == 'm') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          if (*(char *)(unaff_A4 + -0x5c91) == -1) {
            cVar8 = *(char *)(unaff_A4 + -0x6405 + (int)*(short *)(unaff_A4 + -0x5c5a));
            *(char *)(unaff_A4 + -0x5c91) = cVar8;
            uVar10 = cVar8 == '\0';
            (**(code **)(unaff_A4 + -0x7d88))();
          }
          else {
            *(undefined1 *)(unaff_A4 + -0x5c91) = 0xff;
            uVar10 = 0;
          }
        }
      }
      else if (cVar8 == 'r') {
        uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
        if ((bool)uVar10) {
          (**(code **)(unaff_A4 + -0x7f4a))();
        }
      }
      else {
        if (cVar8 != 'c') {
          if (cVar8 == '8') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + 0x1000;
          }
          else if (cVar8 == '2') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + -0x1000;
          }
          else if (cVar8 == '4') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + -0x100;
          }
          else if (cVar8 == '6') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + 0x100;
          }
          uVar10 = 0;
          if ((cVar8 == 'd') && (uVar10 = 0, *(short *)(unaff_A4 + -0x50e6) == 5)) {
            *(undefined2 *)(unaff_A4 + -0x5f74) = 0x80;
            *(undefined2 *)(unaff_A4 + -0x5f7a) = 0;
            uVar2 = ~*(ushort *)(unaff_A4 + -0x408c);
            *(ushort *)(unaff_A4 + -0x408c) = uVar2;
            uVar10 = uVar2 == 0;
          }
          goto LAB_0001ccfa;
        }
        if (*(short *)(unaff_A4 + -0x50e6) == 0) {
          sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
          *(short *)(unaff_A4 + -0x50e6) = sVar6;
          uVar10 = sVar6 == 0;
        }
        else {
          uVar10 = 0;
          if (*(short *)(unaff_A4 + -0x50e6) == 5) {
            *(short *)(unaff_A4 + -0x5c5a) = *(short *)(unaff_A4 + -0x5c5a) + 1;
            uVar10 = 0;
            if (*(short *)(unaff_A4 + -0x5c5a) == 3) {
              *(undefined2 *)(unaff_A4 + -0x5c5a) = 0;
              uVar10 = 1;
            }
          }
        }
      }
      goto LAB_0001ccfa;
    }
    if (*(short *)(unaff_A4 + -0x50e6) == 4) {
      sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
      *(short *)(unaff_A4 + -0x50e6) = sVar6;
      uVar10 = sVar6 == 0;
      goto LAB_0001ccfa;
    }
  }
  *(undefined2 *)(unaff_A4 + -0x50e6) = 0;
  uVar10 = 1;
  goto LAB_0001ccfa;
}


// ==== spawn_enemy_plane @ 00023172 ====

void spawn_enemy_plane(undefined4 param_1,undefined4 param_2)

{
  undefined2 *puVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  int unaff_A4;
  
  sVar4 = -1;
  bVar2 = false;
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    if (*(short *)(unaff_A4 + -0x5dd4 + sVar3 * 0x34) == 0) {
      sVar4 = sVar3;
    }
    if (((*(byte *)(unaff_A4 + -0x5dd1 + sVar3 * 0x34) & 4) != 0) &&
       (*(short *)(unaff_A4 + -0x5dd4 + sVar3 * 0x34) != 0)) {
      bVar2 = true;
    }
  }
  if ((sVar4 != -1) && (((param_1._0_2_ != 0 && (!bVar2)) || (param_1._0_2_ == 0)))) {
    puVar1 = (undefined2 *)(unaff_A4 + -0x5dd4 + sVar4 * 0x34);
    *puVar1 = 2;
    puVar1[10] = param_2._2_2_;
    puVar1[0x10] = param_1._2_2_;
    puVar1[0x12] = 0x32;
    puVar1[0xf] = *(undefined2 *)(unaff_A4 + -0x50ac);
    puVar1[0xe] = *(undefined2 *)(unaff_A4 + -0x50ac);
    puVar1[4] = 0xf0;
    sVar3 = rand_mod();
    puVar1[5] = sVar3 + 5;
    puVar1[3] = 0;
    puVar1[2] = 0;
    puVar1[0xc] = 0;
    puVar1[0xb] = 0;
    puVar1[6] = 0;
    if (param_1._0_2_ == 0) {
      *(short *)(unaff_A4 + -0x5e28) = *(short *)(unaff_A4 + -0x5e28) + 1;
      puVar1[1] = 1;
      puVar1[0x13] = param_2._0_2_;
    }
    else {
      puVar1[1] = 4;
      puVar1[0x13] = 0x32;
    }
  }
  return;
}


// ==== clear_enemy_planes @ 00023178 ====

void clear_enemy_planes(void)

{
  int unaff_A4;
  undefined1 *puStack_10;
  ushort uStack_8;
  short sStack_6;
  
  sStack_6 = 0;
  do {
    puStack_10 = (undefined1 *)(unaff_A4 + -0x5dd4 + sStack_6 * 0x34);
    for (uStack_8 = 0; uStack_8 < 0x34; uStack_8 = uStack_8 + 1) {
      *puStack_10 = 0;
      puStack_10 = puStack_10 + 1;
    }
    sStack_6 = sStack_6 + 1;
  } while (sStack_6 < 4);
  return;
}


// ==== update_enemy_planes @ 0002317e ====

void update_enemy_planes(void)

{
  short sVar1;
  short *psVar2;
  short sVar3;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3198) = 0;
  sVar3 = 0;
  do {
    psVar2 = (short *)(unaff_A4 + -0x5dd4 + sVar3 * 0x34);
    if (*psVar2 != 0) {
      enemy_plane_relation_to_player(psVar2);
      enemy_plane_chase_queue();
      sVar1 = *psVar2;
      if (sVar1 == 1) {
        FUN_0001e4c8(psVar2);
      }
      else if (sVar1 == 2) {
        enemy_plane_ai_flying(psVar2);
        if (((*(byte *)((int)psVar2 + 3) & 4) == 0) && (psVar2[0x12] < 0x21)) {
          psVar2[0x12] = 0x21;
        }
      }
      else if (sVar1 == 4) {
        enemy_plane_falling(psVar2);
      }
      else if ((sVar1 != 8) && (sVar1 == 0x10)) {
        enemy_plane_wreck_burning(psVar2);
      }
      enemy_plane_speed_governor(psVar2);
      if (*psVar2 != 0x10) {
        enemy_plane_move(psVar2);
      }
      enemy_plane_set_sprite(psVar2);
    }
    sVar3 = sVar3 + 1;
  } while (sVar3 < 4);
  return;
}


// ==== sfx_init @ 00023184 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_init(void)

{
  short sVar1;
  undefined4 *puVar2;
  int unaff_A4;
  
  if (*(short *)(unaff_A4 + -0x3196) == 0) {
    *(undefined4 *)(unaff_A4 + -0x3194) = 0;
    sVar1 = 3;
    puVar2 = (undefined4 *)(unaff_A4 + -0x3190);
    do {
      *puVar2 = 0;
      *(undefined2 *)(puVar2 + 2) = 0;
      *(undefined4 *)((int)puVar2 + 0x16) = 0xffffffff;
      puVar2[1] = 0;
      puVar2 = (undefined4 *)((int)puVar2 + 0x1e);
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    _DAT_00dff096 = 0xf;
    _DAT_00dff09e = 0xff;
    *(code **)(unaff_A4 + -0x3118) = _DAT_00000070;
    _DAT_00000070 = audio_interrupt_handler;
    _DAT_00dff09c = 0x780;
    _DAT_00dff09a = 0x8780;
    *(undefined1 *)(unaff_A4 + -0x310c) = 2;
    *(undefined1 *)(unaff_A4 + -0x310b) = 0x1e;
    *(char **)(unaff_A4 + -0x310a) = s_SoundFX_IntHandler_00026154;
    *(code **)(unaff_A4 + -0x3102) = sfx_vbl_server;
    (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0xa8))();
    *(undefined2 *)(unaff_A4 + -0x3196) = 1;
  }
  return 0;
}


// ==== sfx_shutdown @ 0002318a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_shutdown(void)

{
  int unaff_A4;
  
  if (*(short *)(unaff_A4 + -0x3196) != 0) {
    (**(code **)(unaff_A4 + -0x7da6))();
    (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0xc6))();
    (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0xae))();
    _DAT_00dff09a = 0x780;
    _DAT_00dff096 = 0xf;
    _DAT_00000070 = *(undefined4 *)(unaff_A4 + -0x3118);
    *(undefined2 *)(unaff_A4 + -0x3196) = 0;
  }
  return 0;
}


// ==== thunk_FUN_0001e9de @ 00023190 ====

undefined4 thunk_FUN_0001e9de(void)

{
  undefined4 in_D0;
  int unaff_A4;
  
  do {
    if (*(char *)(unaff_A4 + -0x30ea) < '\0') {
      return in_D0;
    }
  } while (DAT_00bfe0ff < '\0');
  return in_D0;
}


// ==== thunk_FUN_0001e9f4 @ 00023196 ====

undefined8 thunk_FUN_0001e9f4(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  *(undefined1 *)(unaff_A4 + -0x30ea) = 0;
  *(undefined1 *)(unaff_A4 + -0x30e9) = 0xff;
  (**(code **)(unaff_A4 + -0x7da0))();
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0xc6))();
  *(undefined1 *)(unaff_A4 + -0x30e8) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0001ea18 @ 0002319c ====

void thunk_FUN_0001ea18(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7da0))();
  *(undefined1 *)(unaff_A4 + -0x30e9) = 0;
  *(undefined1 *)(unaff_A4 + -0x30e8) = 0;
  return;
}


// ==== sfx_start_channel @ 000231a2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sfx_start_channel(void)

{
  undefined4 *puVar1;
  short sVar2;
  uint in_D0;
  short extraout_D1w;
  short extraout_D1w_00;
  short sVar3;
  undefined4 in_D1;
  undefined2 unaff_D2w;
  undefined2 unaff_D3w;
  undefined2 unaff_D4w;
  undefined4 extraout_A0;
  undefined4 extraout_A0_00;
  undefined4 uVar4;
  int in_A0;
  int unaff_A4;
  
  if (in_A0 != 0) {
    if ((short)in_D1 == 6) {
      FUN_0001e9f4();
    }
    sVar2 = (**(code **)(unaff_A4 + -0x7d9a))();
    uVar4 = extraout_A0;
    sVar3 = extraout_D1w;
    if (sVar2 != 0) {
      (**(code **)(unaff_A4 + -0x7da0))();
      uVar4 = extraout_A0_00;
      sVar3 = extraout_D1w_00;
    }
    _DAT_00dff09c = (ushort)(1 << ((ushort)(sVar3 + 7) & 0x1f));
    _DAT_00dff09a = _DAT_00dff09c | 0x8000;
    puVar1 = (undefined4 *)(unaff_A4 + -0x3190 + (int)(short)(sVar3 * 0x1e));
    *(short *)((int)puVar1 + 10) = (short)(in_D0 >> 1);
    *(undefined2 *)(puVar1 + 3) = unaff_D2w;
    *(undefined2 *)((int)puVar1 + 0xe) = unaff_D3w;
    *(undefined2 *)(puVar1 + 4) = 0;
    *(undefined2 *)((int)puVar1 + 0x12) = unaff_D4w;
    *puVar1 = uVar4;
    *(undefined4 *)((int)puVar1 + 0x16) = 0xffffffff;
    *(undefined2 *)(puVar1 + 2) = 1;
  }
  return in_D1;
}


// ==== sfx_stop_all_channels @ 000231a8 ====

void sfx_stop_all_channels(void)

{
  short sVar1;
  int unaff_A4;
  
  do {
    sVar1 = (**(code **)(unaff_A4 + -0x7da0))();
  } while (sVar1 != 0);
  return;
}


// ==== sfx_stop_channel @ 000231ae ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 sfx_stop_channel(void)

{
  undefined4 *puVar1;
  short sVar2;
  uint in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  sVar2 = (short)in_D0;
  puVar1 = (undefined4 *)(unaff_A4 + -0x3190 + (int)(short)(sVar2 * 0x1e));
  _DAT_00dff09a = 0x80 << (in_D0 & 0x3f);
  *(undefined2 *)(puVar1 + 2) = 0;
  _DAT_00dff096 = 1 << (in_D0 & 0x3f);
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 5) = 0xffff;
  *(undefined4 *)((int)puVar1 + 0x16) = 0xffffffff;
  *(undefined2 *)(&DAT_00dff0a8 + (short)(sVar2 << 4)) = 0;
  puVar1[1] = *(undefined4 *)(unaff_A4 + -0x3194);
  *(undefined2 *)(&DAT_00dff0a6 + (short)(sVar2 << 4)) = 0x7c;
  if (sVar2 == 2) {
    *(undefined1 *)(unaff_A4 + -0x30e8) = 0;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== sfx_channel_busy @ 000231b4 ====

undefined8 sfx_channel_busy(void)

{
  undefined4 uVar1;
  undefined4 in_D1;
  int unaff_A4;
  
  uVar1 = 0;
  if (*(int *)(unaff_A4 + -0x3190 + (int)(short)((short)in_D1 * 0x1e)) != 0) {
    uVar1 = 0xffffffff;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== sfx_set_period_volume @ 000231ba ====

void sfx_set_period_volume(void)

{
  int iVar1;
  short in_D0w;
  short in_D1w;
  short unaff_D2w;
  int unaff_A4;
  
  iVar1 = unaff_A4 + -0x3190 + (int)(short)(in_D0w * 0x1e);
  if (-1 < in_D1w) {
    *(short *)(&DAT_00dff0a6 + (short)(in_D0w << 4)) = in_D1w;
  }
  if (-1 < unaff_D2w) {
    *(undefined4 *)(iVar1 + 0x16) = 0xffffffff;
    *(short *)(iVar1 + 0xe) = unaff_D2w;
    *(undefined2 *)(iVar1 + 0x10) = 0;
    *(short *)(&DAT_00dff0a8 + (short)(in_D0w << 4)) = unaff_D2w;
  }
  return;
}


// ==== thunk_FUN_0001edaa @ 000231c0 ====

void thunk_FUN_0001edaa(void)

{
  FUN_0001ed7a();
  FUN_0001ed7a();
  return;
}


// ==== hud_set_ammo_drum @ 000231c6 ====

void hud_set_ammo_drum(void)

{
  int unaff_A4;
  
  *(ushort *)(unaff_A4 + -0x30d4) = (*(byte *)(unaff_A4 + -0x5c91) / 10) * -8 + 0x50;
  *(ushort *)(unaff_A4 + -0x30d2) = ((ushort)*(byte *)(unaff_A4 + -0x5c91) % 10) * -8 + 0x50;
  *(undefined1 *)(unaff_A4 + -0x30c4) = 0xff;
  *(undefined1 *)(unaff_A4 + -0x30b0) = 0xff;
  return;
}


// ==== hud_set_lives_drum @ 000231cc ====

void hud_set_lives_drum(void)

{
  ushort uVar1;
  byte bVar2;
  int unaff_A4;
  
  bVar2 = *(byte *)(unaff_A4 + -0x5ca2);
  if ((char)bVar2 < '\0') {
    bVar2 = 0;
  }
  uVar1 = (ushort)bVar2;
  if (9 < bVar2) {
    uVar1 = 9;
  }
  *(ushort *)(unaff_A4 + -0x30d0) = uVar1 * -8 + 0x59;
  *(undefined1 *)(unaff_A4 + -0x30c2) = 0xff;
  *(undefined1 *)(unaff_A4 + -0x30ae) = 0xff;
  return;
}


// ==== draw_dashboard @ 000231d2 ====

undefined4 draw_dashboard(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  byte bVar4;
  short sVar5;
  short sVar6;
  ushort uVar7;
  int unaff_A4;
  short *psVar8;
  
  psVar8 = (short *)((int)**(short **)(unaff_A4 + -0x41d2) + unaff_A4 + -0x30ce);
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7d70))();
  *(undefined1 *)(unaff_A4 + -0x30a2) = 0xff;
  if (((*(short *)(unaff_A4 + -0x5f7a) != 0) && (*(short *)(unaff_A4 + -0x5f7a) != 1)) &&
     (*(short *)(unaff_A4 + -0x5f7a) != 7)) {
    *(undefined2 *)(unaff_A4 + -0x30a2) = 0;
  }
  draw_enemy_warning_light();
  sVar6 = *(short *)(unaff_A4 + -0x5f74) + -0x60;
  if (*(short *)(unaff_A4 + -0x5f74) < 0x60) {
    sVar6 = 0;
  }
  uVar7 = sVar6 * 2 & 0xfffc;
  if ((*(short *)(unaff_A4 + -0x5f7a) < 2) && (*(short *)(unaff_A4 + -0x3216) != 0)) {
    uVar7 = uVar7 + 0x18;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a6)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a6)) {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a6);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(ushort *)(unaff_A4 + -0x5f74) < 0x74)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x30a0);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x30a0) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x30a0) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x30a0) = 10;
    }
  }
  if ((sVar5 != *psVar8) || (sVar6 != psVar8[1])) {
    *psVar8 = sVar5;
    psVar8[1] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  uVar7 = *(ushort *)(unaff_A4 + -0x5f78);
  if ((short)uVar7 < 0) {
    uVar7 = 0;
  }
  uVar7 = uVar7 >> 1;
  if (0x58 < uVar7) {
    uVar7 = 0x58;
  }
  uVar7 = uVar7 & 0xfffc;
  if ((uVar7 == 0) && (*(short *)(unaff_A4 + -0x30a2) != 0)) {
    uVar7 = (**(code **)(unaff_A4 + -0x7d52))();
    uVar7 = uVar7 >> 0xd & 4;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a4)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a4)) {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a4);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(short *)(unaff_A4 + -0x5f78) < 0x41)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x309e);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x309e) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x309e) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x309e) = 8;
    }
  }
  if ((sVar5 != psVar8[2]) || (sVar6 != psVar8[3])) {
    psVar8[2] = sVar5;
    psVar8[3] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(short *)(unaff_A4 + -0x5c5a) != psVar8[4]) {
    psVar8[4] = *(short *)(unaff_A4 + -0x5c5a);
    (**(code **)(unaff_A4 + -0x7ce0))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5c91);
  if ((bVar4 == 0xff) || ((ushort)bVar4 != psVar8[5])) {
    sVar6 = -1;
    uVar7 = (ushort)bVar4;
    do {
      uVar3 = uVar7;
      sVar6 = sVar6 + 1;
      uVar7 = uVar3 - 10;
    } while (9 < uVar3);
    sVar5 = uVar3 * -8 + 0x50;
    sVar6 = sVar6 * -8 + 0x50;
    if (bVar4 == 0xff) {
      sVar5 = 100;
      sVar6 = 100;
    }
    sVar1 = *(short *)(unaff_A4 + -0x30d4);
    if ((sVar1 == sVar6) && (*(short *)(unaff_A4 + -0x30d2) == sVar5)) {
      psVar8[5] = (ushort)bVar4;
    }
    else {
      uVar7 = *(short *)(unaff_A4 + -0x30d2) + 1;
      if (0x50 < uVar7) {
        uVar7 = 1;
      }
      *(ushort *)(unaff_A4 + -0x30d2) = uVar7;
      if ((sVar1 != sVar6) && (*(ushort *)(unaff_A4 + -0x30d2) < 9)) {
        uVar7 = sVar1 + 1;
        if (0x50 < uVar7) {
          uVar7 = 1;
        }
        *(ushort *)(unaff_A4 + -0x30d4) = uVar7;
      }
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5ca2);
  if ((char)bVar4 < '\0') {
    bVar4 = 0;
  }
  uVar7 = (ushort)bVar4;
  if (9 < bVar4) {
    uVar7 = 9;
  }
  if (uVar7 != psVar8[6]) {
    sVar5 = uVar7 * -8 + 0x59;
    sVar6 = *(short *)(unaff_A4 + -0x30d0);
    if (sVar5 == sVar6) {
      psVar8[6] = uVar7;
    }
    else {
      if (sVar5 < sVar6) {
        sVar6 = sVar6 + -1;
      }
      else {
        sVar6 = sVar6 + 1;
      }
      *(short *)(unaff_A4 + -0x30d0) = sVar6;
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(int *)(unaff_A4 + -0x5cb2) != *(int *)(psVar8 + 8)) {
    *(int *)(psVar8 + 8) = *(int *)(unaff_A4 + -0x5cb2);
    draw_score();
  }
  uVar7 = (ushort)*(byte *)(unaff_A4 + -0x5c7f);
  if (99 < uVar7) {
    uVar7 = 99;
  }
  if (uVar7 != psVar8[7]) {
    psVar8[7] = uVar7;
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x14;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    blit_digit();
    blit_digit();
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1f;
    hud_draw_kill_tally();
    hud_draw_kill_tally();
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return 0;
}


// ==== draw_dashboard @ 000231d8 ====

undefined4 draw_dashboard(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  byte bVar4;
  short sVar5;
  short sVar6;
  ushort uVar7;
  int unaff_A4;
  short *psVar8;
  
  psVar8 = (short *)((int)**(short **)(unaff_A4 + -0x41d2) + unaff_A4 + -0x30ce);
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7d70))();
  *(undefined1 *)(unaff_A4 + -0x30a2) = 0xff;
  if (((*(short *)(unaff_A4 + -0x5f7a) != 0) && (*(short *)(unaff_A4 + -0x5f7a) != 1)) &&
     (*(short *)(unaff_A4 + -0x5f7a) != 7)) {
    *(undefined2 *)(unaff_A4 + -0x30a2) = 0;
  }
  draw_enemy_warning_light();
  sVar6 = *(short *)(unaff_A4 + -0x5f74) + -0x60;
  if (*(short *)(unaff_A4 + -0x5f74) < 0x60) {
    sVar6 = 0;
  }
  uVar7 = sVar6 * 2 & 0xfffc;
  if ((*(short *)(unaff_A4 + -0x5f7a) < 2) && (*(short *)(unaff_A4 + -0x3216) != 0)) {
    uVar7 = uVar7 + 0x18;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a6)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a6)) {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a6);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(ushort *)(unaff_A4 + -0x5f74) < 0x74)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x30a0);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x30a0) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x30a0) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x30a0) = 10;
    }
  }
  if ((sVar5 != *psVar8) || (sVar6 != psVar8[1])) {
    *psVar8 = sVar5;
    psVar8[1] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  uVar7 = *(ushort *)(unaff_A4 + -0x5f78);
  if ((short)uVar7 < 0) {
    uVar7 = 0;
  }
  uVar7 = uVar7 >> 1;
  if (0x58 < uVar7) {
    uVar7 = 0x58;
  }
  uVar7 = uVar7 & 0xfffc;
  if ((uVar7 == 0) && (*(short *)(unaff_A4 + -0x30a2) != 0)) {
    uVar7 = (**(code **)(unaff_A4 + -0x7d52))();
    uVar7 = uVar7 >> 0xd & 4;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a4)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a4)) {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a4);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(short *)(unaff_A4 + -0x5f78) < 0x41)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x309e);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x309e) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x309e) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x309e) = 8;
    }
  }
  if ((sVar5 != psVar8[2]) || (sVar6 != psVar8[3])) {
    psVar8[2] = sVar5;
    psVar8[3] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(short *)(unaff_A4 + -0x5c5a) != psVar8[4]) {
    psVar8[4] = *(short *)(unaff_A4 + -0x5c5a);
    (**(code **)(unaff_A4 + -0x7ce0))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5c91);
  if ((bVar4 == 0xff) || ((ushort)bVar4 != psVar8[5])) {
    sVar6 = -1;
    uVar7 = (ushort)bVar4;
    do {
      uVar3 = uVar7;
      sVar6 = sVar6 + 1;
      uVar7 = uVar3 - 10;
    } while (9 < uVar3);
    sVar5 = uVar3 * -8 + 0x50;
    sVar6 = sVar6 * -8 + 0x50;
    if (bVar4 == 0xff) {
      sVar5 = 100;
      sVar6 = 100;
    }
    sVar1 = *(short *)(unaff_A4 + -0x30d4);
    if ((sVar1 == sVar6) && (*(short *)(unaff_A4 + -0x30d2) == sVar5)) {
      psVar8[5] = (ushort)bVar4;
    }
    else {
      uVar7 = *(short *)(unaff_A4 + -0x30d2) + 1;
      if (0x50 < uVar7) {
        uVar7 = 1;
      }
      *(ushort *)(unaff_A4 + -0x30d2) = uVar7;
      if ((sVar1 != sVar6) && (*(ushort *)(unaff_A4 + -0x30d2) < 9)) {
        uVar7 = sVar1 + 1;
        if (0x50 < uVar7) {
          uVar7 = 1;
        }
        *(ushort *)(unaff_A4 + -0x30d4) = uVar7;
      }
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5ca2);
  if ((char)bVar4 < '\0') {
    bVar4 = 0;
  }
  uVar7 = (ushort)bVar4;
  if (9 < bVar4) {
    uVar7 = 9;
  }
  if (uVar7 != psVar8[6]) {
    sVar5 = uVar7 * -8 + 0x59;
    sVar6 = *(short *)(unaff_A4 + -0x30d0);
    if (sVar5 == sVar6) {
      psVar8[6] = uVar7;
    }
    else {
      if (sVar5 < sVar6) {
        sVar6 = sVar6 + -1;
      }
      else {
        sVar6 = sVar6 + 1;
      }
      *(short *)(unaff_A4 + -0x30d0) = sVar6;
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(int *)(unaff_A4 + -0x5cb2) != *(int *)(psVar8 + 8)) {
    *(int *)(psVar8 + 8) = *(int *)(unaff_A4 + -0x5cb2);
    draw_score();
  }
  uVar7 = (ushort)*(byte *)(unaff_A4 + -0x5c7f);
  if (99 < uVar7) {
    uVar7 = 99;
  }
  if (uVar7 != psVar8[7]) {
    psVar8[7] = uVar7;
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x14;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    blit_digit();
    blit_digit();
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1f;
    hud_draw_kill_tally();
    hud_draw_kill_tally();
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return 0;
}


// ==== clip_dashboard @ 000231de ====

void clip_dashboard(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return;
}


// ==== thunk_FUN_0001f41a @ 000231e4 ====

undefined2 thunk_FUN_0001f41a(void)

{
  ushort uVar1;
  short sVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  int unaff_A4;
  undefined1 auStack_90 [50];
  undefined2 uStack_5e;
  undefined2 uStack_5c;
  undefined2 uStack_5a;
  short sStack_58;
  undefined2 uStack_56;
  undefined4 uStack_54;
  undefined1 auStack_50 [65];
  undefined1 auStack_f [11];
  
  uStack_56 = 0;
  (**(code **)(unaff_A4 + -0x7c5c))((short)(unaff_A4 + -0x470e),(short)auStack_50);
  (**(code **)(unaff_A4 + -0x7e72))();
  uStack_54 = *(undefined4 *)(unaff_A4 + -0x41e2);
  (**(code **)(unaff_A4 + -0x7caa))((short)uStack_54);
  (**(code **)(unaff_A4 + -0x7c9e))();
  (**(code **)(unaff_A4 + -0x7d52))();
  (**(code **)(unaff_A4 + -0x7d52))();
  (**(code **)(unaff_A4 + -0x7d52))();
  (**(code **)(unaff_A4 + -0x7d52))();
  uVar1 = (**(code **)(unaff_A4 + -0x7d52))();
  uVar1 = uVar1 & 0xff;
  while (uVar1 != 0) {
    (**(code **)(unaff_A4 + -0x7d52))();
    uVar1 = uVar1 - 1;
  }
  sStack_58 = (**(code **)(unaff_A4 + -0x7e7e))();
  puVar4 = (undefined2 *)(unaff_A4 + -0x4930 + (sStack_58 % 0x21) * 0x10);
  FUN_0001f374(0x2b,0xa4);
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54,1);
  uStack_5a = *puVar4;
  uStack_5c = puVar4[1];
  uStack_5e = puVar4[2];
  FUN_0001f332(0x30,0xf658);
  FUN_0001f332(0x3d,0xf677);
  FUN_0001f332(0x4a,0xf696);
  FUN_0001f332(0x57,0xf6a7);
  FUN_0001f332(100,0xf6c6);
  FUN_0001f332(0x71,0xf6e5);
  FUN_0001f332(0x82,0xf6f2);
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54,2);
  (**(code **)(unaff_A4 + -0x7bd2))((short)*(undefined4 *)(unaff_A4 + -0x41e2),0x70,0x8c);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_90,0xf70d,uStack_5c);
  FUN_00018570((short)auStack_90);
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54);
  (**(code **)(unaff_A4 + -0x7e6c))((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  (**(code **)(unaff_A4 + -0x7e66))((short)auStack_50);
  auStack_f[0] = 0;
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54,5);
  FUN_0001f374(0x91,0x99);
  (**(code **)(unaff_A4 + -0x7e78))((short)auStack_f,200,0);
  sVar2 = (**(code **)(unaff_A4 + -0x7c62))((short)auStack_f,0xf727);
  if (sVar2 == 0) {
    uStack_56 = 1;
  }
  uVar3 = FUN_0001f2ec((short)auStack_f,(short)(puVar4 + 3));
  sVar2 = (**(code **)(unaff_A4 + -0x7c62))(uVar3);
  if (sVar2 == 0) {
    uStack_56 = 1;
  }
  (**(code **)(unaff_A4 + -0x7e60))();
  return uStack_56;
}


// ==== thunk_FUN_0001fe50 @ 000231ea ====

undefined2 thunk_FUN_0001fe50(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int unaff_A4;
  undefined2 uStack_6;
  
  uStack_6 = 0;
  iVar1 = (**(code **)(unaff_A4 + -0x7c14))(param_1,0x3ee);
  if (iVar1 == 0) {
    uStack_6 = (**(code **)(unaff_A4 + -0x7c20))();
  }
  else {
    iVar2 = (**(code **)(unaff_A4 + -0x7c02))(iVar1,param_2,param_3);
    (**(code **)(unaff_A4 + -0x7c38))(iVar1);
    if (iVar2 != param_3) {
      uStack_6 = (**(code **)(unaff_A4 + -0x7c20))();
    }
  }
  return uStack_6;
}


// ==== thunk_FUN_0001feb4 @ 000231f0 ====

void thunk_FUN_0001feb4(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10001);
  return;
}


// ==== thunk_FUN_0001feca @ 000231f6 ====

void thunk_FUN_0001feca(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10003);
  return;
}


// ==== thunk_FUN_000203be @ 000231fc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_000203be(void)

{
  int unaff_A4;
  
  *(ushort *)(unaff_A4 + -0x46ee) = _DAT_00dff006 ^ *(short *)(unaff_A4 + -0x46ec) * 0x1afb - 0x333U
  ;
  return;
}


// ==== thunk_FUN_000203be @ 00023202 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_000203be(void)

{
  int unaff_A4;
  
  *(ushort *)(unaff_A4 + -0x46ee) = _DAT_00dff006 ^ *(short *)(unaff_A4 + -0x46ec) * 0x1afb - 0x333U
  ;
  return;
}


// ==== thunk_FUN_000203da @ 00023208 ====

void thunk_FUN_000203da(undefined4 param_1)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x46ee) = param_1._0_2_;
  *(undefined2 *)(unaff_A4 + -0x46ec) = param_1._0_2_;
  return;
}


// ==== thunk_FUN_0002044c @ 0002320e ====

void thunk_FUN_0002044c(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  uVar1 = read_fire_button();
  *(undefined2 *)(unaff_A4 + -0x3098) = uVar1;
  return;
}


// ==== thunk_FUN_00020454 @ 00023214 ====

void thunk_FUN_00020454(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  uVar1 = FUN_00020488();
  *(undefined2 *)(unaff_A4 + -0x38bc) = uVar1;
  return;
}


// ==== thunk_FUN_000204f4 @ 0002321a ====

undefined4 thunk_FUN_000204f4(void)

{
  undefined4 extraout_A0;
  
  find_shape_by_name();
  return extraout_A0;
}


// ==== thunk_FUN_0002050e @ 00023220 ====

int thunk_FUN_0002050e(int param_1,undefined4 param_2)

{
  return param_1 + (uint)(ushort)(*(short *)(param_1 + 4) << 3) +
                   *(int *)(param_1 + (uint)(ushort)(param_2._0_2_ + *(short *)(param_1 + 4)) * 4 +
                           6) + 6;
}


// ==== find_shape_by_name @ 00023226 ====

undefined8 find_shape_by_name(void)

{
  int *piVar1;
  int iVar2;
  int in_D0;
  short sVar3;
  undefined4 in_D1;
  int in_A0;
  int *piVar4;
  
  sVar3 = *(short *)(in_A0 + 4);
  if (0 < sVar3) {
    piVar1 = (int *)(in_A0 + 6);
    do {
      piVar4 = piVar1;
      if (in_D0 <= *piVar4) break;
      sVar3 = sVar3 + -1;
      piVar1 = piVar4 + 1;
    } while (sVar3 != -1);
    if (in_D0 == *piVar4) {
      iVar2 = *(short *)(in_A0 + 4) * 8 +
              in_A0 + *(int *)((short)((uint)((int)piVar4 + (-6 - in_A0)) >> 2) * 4 +
                               *(short *)(in_A0 + 4) * 4 + in_A0 + 6) + 6;
      goto LAB_000205ac;
    }
  }
  iVar2 = 0;
LAB_000205ac:
  return CONCAT44(iVar2,in_D1);
}


// ==== thunk_FUN_000205cc @ 0002322c ====

void thunk_FUN_000205cc(undefined4 param_1)

{
  undefined4 uVar1;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x42ce) = param_1._0_2_;
  *(undefined2 *)(unaff_A4 + -0x4346) = 10;
  *(undefined2 *)(unaff_A4 + -0x4348) = 0;
  uVar1 = FUN_00022ba4(0,0);
  *(undefined4 *)(unaff_A4 + -0x4344) = uVar1;
  uVar1 = FUN_00022c8e(*(undefined4 *)(unaff_A4 + -0x4344));
  *(undefined4 *)(unaff_A4 + -0x433c) = uVar1;
  *(int *)(unaff_A4 + -0x432a) = unaff_A4 + -0x4322;
  *(code **)(unaff_A4 + -0x4326) = FUN_0002075a;
  *(undefined1 *)(unaff_A4 + -0x432f) = 0x7f;
  FUN_00022dc4(unaff_A4 + -0x46e8,0,*(undefined4 *)(unaff_A4 + -0x433c),0);
  *(undefined2 *)(*(int *)(unaff_A4 + -0x433c) + 0x1c) = 9;
  *(int *)(*(int *)(unaff_A4 + -0x433c) + 0x28) = unaff_A4 + -0x4338;
  FUN_00022d50(*(undefined4 *)(unaff_A4 + -0x433c));
  uVar1 = FUN_00022ba4(0,0);
  *(undefined4 *)(unaff_A4 + -0x4340) = uVar1;
  uVar1 = FUN_00022cb6(*(undefined4 *)(unaff_A4 + -0x4340),0x20);
  *(undefined4 *)(unaff_A4 + -0x42d2) = uVar1;
  FUN_00022dc4(unaff_A4 + -0x46db,0xffffffff,*(undefined4 *)(unaff_A4 + -0x42d2),0);
  *(undefined4 *)(unaff_A4 + -0x3094) = *(undefined4 *)(*(int *)(unaff_A4 + -0x42d2) + 0x14);
  return;
}


// ==== thunk_FUN_0002067c @ 00023232 ====

void thunk_FUN_0002067c(void)

{
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x42d2) != 0) {
    FUN_00022b88(*(undefined4 *)(unaff_A4 + -0x42d2));
    FUN_00022cfa(*(undefined4 *)(unaff_A4 + -0x42d2));
    *(undefined4 *)(unaff_A4 + -0x42d2) = 0;
    FUN_00022c30(*(undefined4 *)(unaff_A4 + -0x4340));
    *(undefined4 *)(unaff_A4 + -0x4340) = 0;
    *(undefined2 *)(*(int *)(unaff_A4 + -0x433c) + 0x1c) = 10;
    *(int *)(*(int *)(unaff_A4 + -0x433c) + 0x28) = unaff_A4 + -0x4338;
    FUN_00022d50(*(undefined4 *)(unaff_A4 + -0x433c));
    FUN_00022b88(*(undefined4 *)(unaff_A4 + -0x433c));
    FUN_00022ca4(*(undefined4 *)(unaff_A4 + -0x433c));
    *(undefined4 *)(unaff_A4 + -0x433c) = 0;
    FUN_00022c30(*(undefined4 *)(unaff_A4 + -0x4344));
    *(undefined4 *)(unaff_A4 + -0x4344) = 0;
  }
  return;
}


// ==== thunk_FUN_000206ee @ 00023238 ====

void thunk_FUN_000206ee(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_000207e4();
  FUN_00020700(uVar1);
  return;
}


// ==== thunk_FUN_00020700 @ 0002323e ====

ushort thunk_FUN_00020700(undefined4 param_1)

{
  short sVar1;
  byte abStack_20 [2];
  undefined4 uStack_1e;
  undefined1 uStack_1a;
  undefined1 uStack_19;
  undefined2 uStack_18;
  undefined2 uStack_16;
  ushort uStack_6;
  
  uStack_6 = 0;
  uStack_1e = 0;
  uStack_1a = 1;
  uStack_19 = 0;
  uStack_18 = param_1._2_2_;
  uStack_16 = (undefined2)((uint)param_1 >> 0x10);
  sVar1 = FUN_00022f30(&uStack_1e,abStack_20,1,0);
  if (sVar1 == 1) {
    uStack_6 = (ushort)abStack_20[0];
  }
  return uStack_6;
}


// ==== thunk_FUN_0002075a @ 00023244 ====

void thunk_FUN_0002075a(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int *in_A0;
  
  do {
    sVar3 = DAT_00026c06;
    uVar1 = *(ushort *)((int)in_A0 + 6);
    uVar2 = *(ushort *)(in_A0 + 2);
    if (*(char *)(in_A0 + 1) == '\x02') {
      if (uVar1 == 0x69) {
        DAT_00027ebe = CONCAT11(0xff,(undefined1)DAT_00027ebe);
      }
      if (uVar1 == 0xe9) {
        DAT_00027ebe = 0;
        goto LAB_0002078c;
      }
    }
    else {
LAB_0002078c:
      if (((*(char *)(in_A0 + 1) == '\x01') && ((uVar1 & 0x80) == 0)) &&
         ((DAT_00026c80 == 0 || ((DAT_00026c80 & uVar2) != 0)))) {
        if (DAT_00026c06 < DAT_00026c08) {
          (&DAT_00026be8)[DAT_00026c06] = (char)uVar1;
          *(ushort *)((int)&DAT_00026bf2 + (int)(short)(sVar3 * 2)) = uVar2;
          DAT_00026c06 = DAT_00026c06 + 1;
        }
        *(undefined2 *)(in_A0 + 1) = 0;
      }
    }
    in_A0 = (int *)*in_A0;
    if (in_A0 == (int *)0x0) {
      return;
    }
  } while( true );
}


// ==== thunk_FUN_000207d8 @ 0002324a ====

undefined4 thunk_FUN_000207d8(void)

{
  undefined4 uVar1;
  int unaff_A4;
  
  uVar1 = 0;
  if (*(short *)(unaff_A4 + -0x4348) != 0) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// ==== thunk_FUN_000207e4 @ 00023250 ====

undefined8 thunk_FUN_000207e4(void)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  short sVar4;
  undefined4 in_D1;
  short sVar5;
  int unaff_A4;
  undefined1 in_ZF;
  
  while( true ) {
    FUN_000207d8();
    if (!(bool)in_ZF) break;
    (**(code **)(unaff_A4 + -0x7bae))();
  }
  (**(code **)(unaff_A4 + -0x7bfc))();
  uVar1 = *(ushort *)(unaff_A4 + -0x435c);
  bVar2 = *(byte *)(unaff_A4 + -0x4366);
  uVar3 = CONCAT31((int3)(((uint)uVar1 << 0x10) >> 8),bVar2);
  *(short *)(unaff_A4 + -0x4348) = *(short *)(unaff_A4 + -0x4348) + -1;
  sVar4 = 0;
  sVar5 = 0;
  do {
    *(undefined1 *)(unaff_A4 + -0x4366 + (int)sVar4) =
         *(undefined1 *)(unaff_A4 + -0x4365 + (int)sVar4);
    *(undefined2 *)(unaff_A4 + -0x435c + (int)sVar5) =
         *(undefined2 *)(unaff_A4 + -0x435a + (int)sVar5);
    sVar4 = sVar4 + 1;
    sVar5 = sVar5 + 2;
  } while (sVar4 <= *(short *)(unaff_A4 + -0x4348));
  (**(code **)(unaff_A4 + -0x7bf6))();
  if (*(ushort *)(unaff_A4 + -0x42ce) != 0) {
    uVar3 = (uint)(~*(ushort *)(unaff_A4 + -0x42ce) & uVar1) << 0x10 | (uint)bVar2;
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== thunk_FUN_00020848 @ 00023256 ====

void thunk_FUN_00020848(undefined4 param_1)

{
  FUN_00020874(param_1,0x10001);
  return;
}


// ==== thunk_FUN_0002085e @ 0002325c ====

void thunk_FUN_0002085e(undefined4 param_1)

{
  FUN_00020874(param_1,0x10003);
  return;
}


// ==== thunk_FUN_0002090a @ 00023262 ====

undefined4 thunk_FUN_0002090a(int param_1)

{
  undefined4 *puVar1;
  int unaff_A4;
  
  if (param_1 != 0) {
    if (param_1 == -1) {
      while (*(int *)(unaff_A4 + -0x46cc) != 0) {
        FUN_0002090a(*(int *)(unaff_A4 + -0x46cc) + 0xc);
      }
    }
    else {
      puVar1 = (undefined4 *)(param_1 + -0xc);
      if (puVar1 == *(undefined4 **)(unaff_A4 + -0x46cc)) {
        *(undefined4 *)(unaff_A4 + -0x46cc) = *(undefined4 *)(param_1 + -8);
      }
      if (puVar1 == *(undefined4 **)(param_1 + -8)) {
        *(undefined4 *)(unaff_A4 + -0x46cc) = 0;
      }
      *(undefined4 *)(*(int *)(param_1 + -8) + 8) = *(undefined4 *)(param_1 + -4);
      *(undefined4 *)(*(int *)(param_1 + -4) + 4) = *(undefined4 *)(param_1 + -8);
      thunk_FUN_00022d8a(puVar1,*puVar1);
    }
  }
  return 0;
}


// ==== thunk_FUN_00020aee @ 00023268 ====

void thunk_FUN_00020aee(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  blit_shape();
                    /* WARNING: Could not recover jumptable at 0x00020b08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== blit_shape @ 0002326e ====

undefined8 blit_shape(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  byte bVar6;
  byte bVar7;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar8;
  ushort uVar9;
  byte bVar10;
  int iVar11;
  int in_A0;
  int *piVar12;
  int unaff_A4;
  byte *pbVar13;
  int unaff_A6;
  undefined1 in_CF;
  
  blit_clip_setup();
  if (!(bool)in_CF) {
    bVar6 = *(byte *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
    iVar11 = *(int *)(unaff_A4 + -0x3078);
    iVar2 = *(int *)(unaff_A4 + -0x3074);
    sVar3 = *(short *)(unaff_A4 + -0x3066);
    uVar4 = *(undefined2 *)(unaff_A4 + -0x306e);
    sVar5 = *(short *)(unaff_A4 + -0x3070);
    uVar8 = *(ushort *)(unaff_A4 + -0x3060) << 0xc | *(ushort *)(unaff_A4 + -0x3060) >> 4;
    bVar10 = *(byte *)(unaff_A6 + 2);
    while ((bVar10 & 0x40) != 0) {
      bVar10 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(unaff_A4 + -0x305e);
    *(undefined2 *)(unaff_A6 + 0x46) = *(undefined2 *)(unaff_A4 + -0x305c);
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    uVar9 = 0xbca;
    if (iVar2 == 0) {
      uVar9 = 0x3ca;
      *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
      if (uVar8 == 0) {
        uVar9 = 0x1ca;
        *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
      }
    }
    uVar9 = uVar9 | uVar8;
    *(undefined2 *)(unaff_A6 + 100) = *(undefined2 *)(unaff_A4 + -0x3068);
    *(undefined2 *)(unaff_A6 + 0x62) = *(undefined2 *)(unaff_A4 + -0x306a);
    *(undefined2 *)(unaff_A6 + 0x60) = *(undefined2 *)(unaff_A4 + -0x306c);
    *(undefined2 *)(unaff_A6 + 0x66) = *(undefined2 *)(unaff_A4 + -0x306c);
    bVar10 = bVar6 & *(byte *)(in_A0 + 0xc);
    if (bVar10 != 0) {
      piVar12 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0;
      do {
        bVar7 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar7 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar2;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
          bVar7 = *(byte *)(unaff_A6 + 2);
          while ((bVar7 & 0x40) != 0) {
            bVar7 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    bVar10 = bVar6 & *(byte *)(in_A0 + 0xd);
    if (bVar10 != 0) {
      piVar12 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar7 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar7 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar2;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
          bVar7 = *(byte *)(unaff_A6 + 2);
          while ((bVar7 & 0x40) != 0) {
            bVar7 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar8;
    *(ushort *)(unaff_A6 + 0x40) = uVar9 | 0x400;
    pbVar13 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar13 == 0) break;
      bVar10 = bVar6 & *pbVar13;
      if (bVar10 != 0) {
        piVar12 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        do {
          bVar7 = bVar10 & 1;
          bVar10 = bVar10 >> 1;
          if (bVar7 != 0) {
            iVar1 = *piVar12;
            *(int *)(unaff_A6 + 0x50) = iVar2;
            *(int *)(unaff_A6 + 0x4c) = iVar11;
            *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar7 = *(byte *)(unaff_A6 + 2);
            while ((bVar7 & 0x40) != 0) {
              bVar7 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar12 = piVar12 + 1;
        } while (bVar10 != 0);
      }
      iVar11 = sVar3 + iVar11;
      pbVar13 = pbVar13 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00020cc4 @ 00023274 ====

void thunk_FUN_00020cc4(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  draw_shape_automask();
                    /* WARNING: Could not recover jumptable at 0x00020cde. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== draw_shape_automask @ 0002327a ====

undefined4 draw_shape_automask(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  undefined2 uVar4;
  char cVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  undefined4 uVar9;
  ushort uVar10;
  ushort uVar11;
  undefined4 in_D0;
  short sVar12;
  byte bVar13;
  int iVar14;
  uint *puVar15;
  ushort *in_A0;
  ushort *puVar16;
  uint *puVar17;
  int in_A1;
  uint *puVar18;
  int *piVar19;
  uint *puVar20;
  int unaff_A4;
  uint *puVar21;
  uint *puVar22;
  int unaff_A6;
  bool bVar23;
  
  bVar23 = false;
  if (in_A1 != 0) {
    blit_clip_setup();
    if (!bVar23) {
      bVar6 = *(byte *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
      iVar14 = *(int *)(unaff_A4 + -0x3078);
      iVar2 = *(int *)(unaff_A4 + -0x3074);
      sVar3 = *(short *)(unaff_A4 + -0x3066);
      uVar4 = *(undefined2 *)(unaff_A4 + -0x306e);
      sVar12 = *(short *)(unaff_A4 + -0x3070);
      uVar10 = *(ushort *)(unaff_A4 + -0x3060) << 0xc | *(ushort *)(unaff_A4 + -0x3060) >> 4;
      bVar13 = *(byte *)(unaff_A6 + 2);
      while ((bVar13 & 0x40) != 0) {
        bVar13 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(unaff_A4 + -0x305e);
      *(undefined2 *)(unaff_A6 + 0x46) = *(undefined2 *)(unaff_A4 + -0x305c);
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar11 = 0xbca;
      if (iVar2 == 0) {
        uVar11 = 0x3ca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        if (uVar10 == 0) {
          uVar11 = 0x1ca;
          *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
        }
      }
      uVar11 = uVar11 | uVar10;
      *(undefined2 *)(unaff_A6 + 100) = *(undefined2 *)(unaff_A4 + -0x3068);
      *(undefined2 *)(unaff_A6 + 0x62) = *(undefined2 *)(unaff_A4 + -0x306a);
      *(undefined2 *)(unaff_A6 + 0x60) = *(undefined2 *)(unaff_A4 + -0x306c);
      *(undefined2 *)(unaff_A6 + 0x66) = *(undefined2 *)(unaff_A4 + -0x306c);
      bVar13 = bVar6 & *(byte *)(in_A0 + 6);
      if (bVar13 != 0) {
        piVar19 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0;
        do {
          bVar7 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar7 != 0) {
            iVar1 = *piVar19;
            *(int *)(unaff_A6 + 0x50) = iVar2;
            *(int *)(unaff_A6 + 0x48) = sVar12 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar12 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar7 = *(byte *)(unaff_A6 + 2);
            while ((bVar7 & 0x40) != 0) {
              bVar7 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar19 = piVar19 + 1;
        } while (bVar13 != 0);
      }
      bVar13 = bVar6 & *(byte *)((int)in_A0 + 0xd);
      if (bVar13 != 0) {
        piVar19 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        do {
          bVar7 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar7 != 0) {
            iVar1 = *piVar19;
            *(int *)(unaff_A6 + 0x50) = iVar2;
            *(int *)(unaff_A6 + 0x48) = sVar12 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar12 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar7 = *(byte *)(unaff_A6 + 2);
            while ((bVar7 & 0x40) != 0) {
              bVar7 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar19 = piVar19 + 1;
        } while (bVar13 != 0);
      }
      *(ushort *)(unaff_A6 + 0x42) = uVar10;
      *(ushort *)(unaff_A6 + 0x40) = uVar11 | 0x400;
      puVar16 = in_A0 + 7;
      while( true ) {
        if (*(byte *)puVar16 == 0) break;
        bVar13 = bVar6 & *(byte *)puVar16;
        if (bVar13 != 0) {
          piVar19 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
          do {
            bVar7 = bVar13 & 1;
            bVar13 = bVar13 >> 1;
            if (bVar7 != 0) {
              iVar1 = *piVar19;
              *(int *)(unaff_A6 + 0x50) = iVar2;
              *(int *)(unaff_A6 + 0x4c) = iVar14;
              *(int *)(unaff_A6 + 0x48) = sVar12 + iVar1;
              *(int *)(unaff_A6 + 0x54) = sVar12 + iVar1;
              *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
              bVar7 = *(byte *)(unaff_A6 + 2);
              while ((bVar7 & 0x40) != 0) {
                bVar7 = *(byte *)(unaff_A6 + 2);
              }
            }
            piVar19 = piVar19 + 1;
          } while (bVar13 != 0);
        }
        iVar14 = sVar3 + iVar14;
        puVar16 = (ushort *)((int)puVar16 + 1);
      }
    }
    return in_D0;
  }
  uVar8 = (uint)*in_A0 * (uint)in_A0[1];
  if (*(uint *)(unaff_A4 + -0x3bc4) <= uVar8 && uVar8 - *(uint *)(unaff_A4 + -0x3bc4) != 0) {
    uVar9 = blit_shape();
    return uVar9;
  }
  puVar16 = in_A0 + 7;
  sVar3 = -1;
  do {
    sVar12 = sVar3;
    cVar5 = *(char *)puVar16;
    puVar16 = (ushort *)((int)puVar16 + 1);
    sVar3 = sVar12 + 1;
  } while (cVar5 != '\0');
  if ((short)(sVar12 + 1) != 0 && sVar12 != 0) {
    puVar17 = *(uint **)(unaff_A4 + -0x3bc8);
    puVar15 = (uint *)(in_A0 + 10);
    uVar11 = (ushort)uVar8;
    puVar18 = (uint *)((int)puVar15 + (int)(short)uVar11);
    puVar20 = (uint *)((int)puVar18 + (int)(short)uVar11);
    puVar21 = (uint *)((int)puVar20 + (int)(short)uVar11);
    puVar22 = (uint *)((int)puVar21 + (int)(short)uVar11);
    uVar10 = uVar11 >> 1;
    if (sVar12 == 1) {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 = *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
      }
    }
    else if (sVar12 == 2) {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 = *(ushort *)puVar20 | *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar20 = (uint *)((int)puVar20 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar20 | *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar20 = puVar20 + 1;
      }
    }
    else if (sVar12 == 3) {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 =
             *(ushort *)puVar21 | *(ushort *)puVar20 | *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar20 = (uint *)((int)puVar20 + 2);
        puVar21 = (uint *)((int)puVar21 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar21 | *puVar20 | *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar20 = puVar20 + 1;
        puVar21 = puVar21 + 1;
      }
    }
    else {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 =
             *(ushort *)puVar22 |
             *(ushort *)puVar21 | *(ushort *)puVar20 | *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar20 = (uint *)((int)puVar20 + 2);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar22 = (uint *)((int)puVar22 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar22 | *puVar21 | *puVar20 | *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar20 = puVar20 + 1;
        puVar21 = puVar21 + 1;
        puVar22 = puVar22 + 1;
      }
    }
  }
  uVar9 = blit_shape();
  return uVar9;
}


// ==== thunk_FUN_00020e0a @ 00023280 ====

void thunk_FUN_00020e0a(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  blit_shape_xor();
                    /* WARNING: Could not recover jumptable at 0x00020e20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== blit_shape_xor @ 00023286 ====

undefined8 blit_shape_xor(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  byte bVar5;
  byte bVar6;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar7;
  byte bVar8;
  int iVar9;
  int in_A0;
  int iVar10;
  int *piVar11;
  int unaff_A4;
  byte *pbVar12;
  int unaff_A6;
  undefined1 in_CF;
  
  blit_clip_setup();
  if (!(bool)in_CF) {
    bVar5 = *(byte *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
    iVar9 = *(int *)(unaff_A4 + -0x3078);
    sVar1 = *(short *)(unaff_A4 + -0x3066);
    uVar2 = *(undefined2 *)(unaff_A4 + -0x306e);
    sVar3 = *(short *)(unaff_A4 + -0x3070);
    uVar7 = *(ushort *)(unaff_A4 + -0x3060) << 0xc | *(ushort *)(unaff_A4 + -0x3060) >> 4;
    bVar8 = *(byte *)(unaff_A6 + 2);
    while ((bVar8 & 0x40) != 0) {
      bVar8 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(unaff_A4 + -0x305e);
    sVar4 = *(short *)(unaff_A4 + -0x305a);
    *(short *)(unaff_A6 + 0x46) = sVar4;
    if (sVar4 == 0) {
      *(undefined2 *)(unaff_A6 + 0x46) = *(undefined2 *)(unaff_A4 + -0x305c);
    }
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
    *(undefined2 *)(unaff_A6 + 0x62) = *(undefined2 *)(unaff_A4 + -0x306a);
    *(undefined2 *)(unaff_A6 + 0x60) = *(undefined2 *)(unaff_A4 + -0x306c);
    *(undefined2 *)(unaff_A6 + 0x66) = *(undefined2 *)(unaff_A4 + -0x306c);
    *(int *)(unaff_A6 + 0x4c) = iVar9;
    bVar8 = bVar5 & *(byte *)(in_A0 + 0xd);
    if (bVar8 != 0) {
      piVar11 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x36a;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar6 = bVar8 & 1;
        bVar8 = bVar8 >> 1;
        if (bVar6 != 0) {
          iVar10 = (int)sVar3 + *piVar11;
          *(int *)(unaff_A6 + 0x48) = iVar10;
          *(int *)(unaff_A6 + 0x54) = iVar10;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar2;
          bVar6 = *(byte *)(unaff_A6 + 2);
          while ((bVar6 & 0x40) != 0) {
            bVar6 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar11 = piVar11 + 1;
      } while (bVar8 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar7;
    *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x76a;
    pbVar12 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar12 == 0) break;
      bVar8 = bVar5 & *pbVar12;
      if (bVar8 != 0) {
        piVar11 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        do {
          bVar6 = bVar8 & 1;
          bVar8 = bVar8 >> 1;
          if (bVar6 != 0) {
            iVar10 = (int)sVar3 + *piVar11;
            *(int *)(unaff_A6 + 0x4c) = iVar9;
            *(int *)(unaff_A6 + 0x48) = iVar10;
            *(int *)(unaff_A6 + 0x54) = iVar10;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar2;
            bVar6 = *(byte *)(unaff_A6 + 2);
            while ((bVar6 & 0x40) != 0) {
              bVar6 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar11 = piVar11 + 1;
        } while (bVar8 != 0);
      }
      iVar9 = sVar1 + iVar9;
      pbVar12 = pbVar12 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00020ff2 @ 0002328c ====

void thunk_FUN_00020ff2(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  fill_rect();
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== fill_rect @ 00023292 ====

undefined8 fill_rect(void)

{
  short *psVar1;
  short sVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  ushort uVar8;
  uint in_D0;
  uint uVar9;
  short sVar10;
  uint in_D1;
  undefined2 uVar11;
  ushort unaff_D2w;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar12;
  ushort uVar13;
  undefined3 uVar14;
  undefined4 unaff_D7;
  int iVar15;
  int *piVar16;
  int *piVar17;
  int unaff_A4;
  int unaff_A6;
  
  uVar7 = in_D0;
  if ((short)in_D0 < *(short *)(unaff_A4 + -0x469e)) {
    uVar7 = (uint)*(ushort *)(unaff_A4 + -0x469e);
  }
  if (*(short *)(unaff_A4 + -0x469c) <= (short)unaff_D2w) {
    unaff_D2w = *(short *)(unaff_A4 + -0x469c) - 1;
  }
  uVar9 = in_D1;
  if ((short)in_D1 < *(short *)(unaff_A4 + -0x46a2)) {
    uVar9 = (uint)*(ushort *)(unaff_A4 + -0x46a2);
  }
  if (*(short *)(unaff_A4 + -0x46a0) <= unaff_D3w) {
    unaff_D3w = *(short *)(unaff_A4 + -0x46a0) + -1;
  }
  uVar8 = (ushort)uVar7;
  sVar10 = (short)uVar9;
  uVar14 = (undefined3)((uint)unaff_D7 >> 8);
  if (((uVar8 | unaff_D2w + 1) & 0xf) != 0) {
    sVar4 = (unaff_D3w - sVar10) + 1;
    if (sVar4 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
      psVar1 = *(short **)(unaff_A4 + -0x3eb0);
      sVar2 = *psVar1;
      uVar13 = (short)uVar8 >> 3 & 0xfffe;
      sVar5 = ((short)unaff_D2w >> 3 & 0xfffeU) + 2;
      bVar3 = *(byte *)(unaff_A6 + 2);
      while ((bVar3 & 0x40) != 0) {
        bVar3 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) =
           *(undefined2 *)(unaff_A4 + -0x4696 + (int)(short)((uVar8 & 0xf) * 2));
      *(undefined2 *)(unaff_A6 + 0x46) =
           *(undefined2 *)(unaff_A4 + -0x4672 + (int)(short)((unaff_D2w & 0xf) * 2));
      uVar8 = sVar5 - uVar13;
      if (uVar8 != 0 && (short)uVar13 <= sVar5) {
        sVar5 = *psVar1;
        *(ushort *)(unaff_A6 + 0x62) = sVar5 - uVar8;
        *(ushort *)(unaff_A6 + 0x66) = sVar5 - uVar8;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x42) = 0;
        uVar12 = (ushort)*(byte *)((int)psVar1 + 5);
        uVar7 = CONCAT31(uVar14,*(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18));
        piVar17 = (int *)(psVar1 + 4);
        while (uVar12 = uVar12 - 1, uVar12 != 0xffff) {
          piVar16 = piVar17 + 1;
          iVar15 = *piVar17;
          uVar11 = 0x50c;
          uVar9 = unaff_D4 & 1;
          unaff_D4 = unaff_D4 >> 1 & 0x7fff;
          if (uVar9 != 0) {
            uVar11 = 0x5fc;
          }
          uVar9 = uVar7 & 1;
          uVar7 = uVar7 >> 1 & 0x7fff;
          piVar17 = piVar16;
          if (uVar9 != 0) {
            iVar15 = (short)(uVar13 + sVar10 * sVar2) + iVar15;
            bVar3 = *(byte *)(unaff_A6 + 2);
            while ((bVar3 & 0x40) != 0) {
              bVar3 = *(byte *)(unaff_A6 + 2);
            }
            *(int *)(unaff_A6 + 0x4c) = iVar15;
            *(int *)(unaff_A6 + 0x54) = iVar15;
            *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
            *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar4 * 0x40;
          }
        }
      }
    }
    return CONCAT44(in_D0,in_D1);
  }
  sVar4 = (unaff_D3w - sVar10) + 1;
  if (sVar4 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
    psVar1 = *(short **)(unaff_A4 + -0x3eb0);
    sVar2 = *psVar1;
    sVar5 = (short)(uVar8 + 0xf & 0xfff0) >> 3;
    sVar6 = (short)(unaff_D2w + 1 & 0xfff0) >> 3;
    bVar3 = *(byte *)(unaff_A6 + 2);
    while ((bVar3 & 0x40) != 0) {
      bVar3 = *(byte *)(unaff_A6 + 2);
    }
    uVar8 = sVar6 - sVar5;
    if (uVar8 != 0 && sVar5 <= sVar6) {
      *(ushort *)(unaff_A6 + 0x66) = *psVar1 - uVar8;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar1 + 5);
      uVar7 = CONCAT31(uVar14,*(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18));
      piVar17 = (int *)(psVar1 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar16 = piVar17 + 1;
        iVar15 = *piVar17;
        uVar11 = 0x100;
        uVar9 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar9 != 0) {
          uVar11 = 0x1ff;
        }
        uVar9 = uVar7 & 1;
        uVar7 = uVar7 >> 1 & 0x7fff;
        piVar17 = piVar16;
        if (uVar9 != 0) {
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar5 + sVar10 * sVar2) + iVar15;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
          *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar4 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00021120 @ 00023298 ====

undefined8 thunk_FUN_00021120(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  fill_rect_aligned();
  (**(code **)(unaff_A4 + -0x7c8c))();
  return CONCAT44(in_D0,in_D1);
}


// ==== fill_rect_aligned @ 0002329e ====

undefined8 fill_rect_aligned(void)

{
  int iVar1;
  short *psVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  ushort uVar6;
  short sVar7;
  short sVar8;
  uint uVar9;
  uint uVar10;
  uint in_D0;
  uint uVar11;
  uint in_D1;
  undefined2 uVar12;
  short unaff_D2w;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar13;
  undefined4 unaff_D7;
  int *piVar14;
  int *piVar15;
  int unaff_A4;
  int unaff_A6;
  
  uVar10 = in_D0;
  if ((short)in_D0 < *(short *)(unaff_A4 + -0x469e)) {
    uVar10 = (uint)*(ushort *)(unaff_A4 + -0x469e);
  }
  if (*(short *)(unaff_A4 + -0x469c) <= unaff_D2w) {
    unaff_D2w = *(short *)(unaff_A4 + -0x469c) + -1;
  }
  uVar11 = in_D1;
  if ((short)in_D1 < *(short *)(unaff_A4 + -0x46a2)) {
    uVar11 = (uint)*(ushort *)(unaff_A4 + -0x46a2);
  }
  if (*(short *)(unaff_A4 + -0x46a0) <= unaff_D3w) {
    unaff_D3w = *(short *)(unaff_A4 + -0x46a0) + -1;
  }
  sVar5 = unaff_D3w - (short)uVar11;
  sVar4 = sVar5 + 1;
  if (sVar4 != 0 && -2 < sVar5) {
    psVar2 = *(short **)(unaff_A4 + -0x3eb0);
    sVar5 = *psVar2;
    sVar7 = (short)((short)uVar10 + 0xfU & 0xfff0) >> 3;
    sVar8 = (short)(unaff_D2w + 1U & 0xfff0) >> 3;
    bVar3 = *(byte *)(unaff_A6 + 2);
    while ((bVar3 & 0x40) != 0) {
      bVar3 = *(byte *)(unaff_A6 + 2);
    }
    uVar6 = sVar8 - sVar7;
    if (uVar6 != 0 && sVar7 <= sVar8) {
      *(ushort *)(unaff_A6 + 0x66) = *psVar2 - uVar6;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar2 + 5);
      uVar10 = CONCAT31((int3)((uint)unaff_D7 >> 8),
                        *(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18));
      piVar15 = (int *)(psVar2 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar14 = piVar15 + 1;
        iVar1 = *piVar15;
        uVar12 = 0x100;
        uVar9 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar9 != 0) {
          uVar12 = 0x1ff;
        }
        uVar9 = uVar10 & 1;
        uVar10 = uVar10 >> 1 & 0x7fff;
        piVar15 = piVar14;
        if (uVar9 != 0) {
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar7 + (short)uVar11 * sVar5) + iVar1;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar12;
          *(ushort *)(unaff_A6 + 0x58) = uVar6 >> 1 | sVar4 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00021246 @ 000232a4 ====

undefined4 thunk_FUN_00021246(int param_1)

{
  int iVar1;
  ushort uVar2;
  undefined4 in_D0;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int unaff_A4;
  
  *(int *)(unaff_A4 + -0x40e4) = param_1;
  iVar1 = *(int *)(param_1 + 4);
  *(int *)(unaff_A4 + -0x3eb0) = iVar1;
  *(byte *)(param_1 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = (undefined4 *)(unaff_A4 + -0x46c2);
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== set_rastport @ 000232aa ====

undefined4 set_rastport(void)

{
  int iVar1;
  ushort uVar2;
  undefined4 in_D0;
  undefined4 *puVar3;
  int in_A0;
  undefined4 *puVar4;
  int unaff_A4;
  
  *(int *)(unaff_A4 + -0x40e4) = in_A0;
  iVar1 = *(int *)(in_A0 + 4);
  *(int *)(unaff_A4 + -0x3eb0) = iVar1;
  *(byte *)(in_A0 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = (undefined4 *)(unaff_A4 + -0x46c2);
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== set_clip_full_bitmap @ 000232b0 ====

undefined8 set_clip_full_bitmap(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  set_clip_rect();
  return CONCAT44(in_D0,in_D1);
}


// ==== set_clip_rect @ 000232b6 ====

void set_clip_rect(void)

{
  undefined2 in_D0w;
  undefined2 in_D1w;
  undefined2 unaff_D2w;
  undefined2 unaff_D3w;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x46a2) = in_D0w;
  *(undefined2 *)(unaff_A4 + -0x46a0) = in_D1w;
  *(undefined2 *)(unaff_A4 + -0x469e) = unaff_D2w;
  *(undefined2 *)(unaff_A4 + -0x469c) = unaff_D3w;
  *(ushort *)(unaff_A4 + -0x469e) = *(ushort *)(unaff_A4 + -0x469e) & 0xfff0;
  *(ushort *)(unaff_A4 + -0x469c) = *(ushort *)(unaff_A4 + -0x469c) & 0xfff0;
  *(undefined2 *)(unaff_A4 + -0x4698) = *(undefined2 *)(unaff_A4 + -0x469c);
  *(short *)(unaff_A4 + -0x4698) = *(short *)(unaff_A4 + -0x4698) + -1;
  *(undefined2 *)(unaff_A4 + -0x469a) = *(undefined2 *)(unaff_A4 + -0x46a0);
  *(short *)(unaff_A4 + -0x469a) = *(short *)(unaff_A4 + -0x469a) + -1;
  return;
}


// ==== own_blitter @ 000232bc ====

void own_blitter(void)

{
  FUN_00022e8a();
  return;
}


// ==== wait_disown_blitter @ 000232c2 ====

void wait_disown_blitter(void)

{
  do {
  } while ((DAT_00dff002 & 0x40) != 0);
  FUN_00022e40();
  return;
}


// ==== draw_line_clipped @ 000232c8 ====

undefined8 draw_line_clipped(void)

{
  ushort *puVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  uint uVar6;
  uint in_D0;
  uint uVar7;
  uint in_D1;
  ushort uVar8;
  ushort unaff_D2w;
  ushort unaff_D3w;
  ushort uVar10;
  int iVar9;
  uint unaff_D4;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  uint uVar14;
  ushort *puVar15;
  ushort *puVar16;
  int iVar17;
  int unaff_A4;
  int unaff_A6;
  undefined4 uStack_34;
  
  *(undefined2 *)(unaff_A4 + -0x469a) = *(undefined2 *)(unaff_A4 + -0x46a0);
  *(undefined2 *)(unaff_A4 + -0x4698) = *(undefined2 *)(unaff_A4 + -0x469c);
  *(short *)(unaff_A4 + -0x469a) = *(short *)(unaff_A4 + -0x469a) + -1;
  *(short *)(unaff_A4 + -0x4698) = *(short *)(unaff_A4 + -0x4698) + -1;
  uVar14 = unaff_D4 & 0xffff;
  uVar10 = 10;
  if ((*(short *)(unaff_A4 + -0x469e) <= (short)unaff_D2w) &&
     (uVar10 = 2, *(short *)(unaff_A4 + -0x4698) < (short)unaff_D2w)) {
    uVar10 = 6;
  }
  if ((*(short *)(unaff_A4 + -0x46a2) <= (short)unaff_D3w) &&
     (uVar10 = uVar10 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)unaff_D3w)) {
    uVar10 = uVar10 | 1;
  }
  uVar11 = 10;
  if ((*(short *)(unaff_A4 + -0x469e) <= (short)in_D0) &&
     (uVar11 = 2, *(short *)(unaff_A4 + -0x4698) < (short)in_D0)) {
    uVar11 = 6;
  }
  if ((*(short *)(unaff_A4 + -0x46a2) <= (short)in_D1) &&
     (uVar11 = uVar11 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)in_D1)) {
    uVar11 = uVar11 | 1;
  }
  uStack_34 = CONCAT22(uVar11,uVar10);
  uVar6 = in_D0;
  uVar7 = in_D1;
  while( true ) {
    uVar10 = (ushort)uVar6;
    uVar11 = (ushort)uVar7;
    if (uStack_34._2_2_ == 0 && uStack_34._0_2_ == 0) {
      *(undefined1 *)(unaff_A4 + -0x3051) = *(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
      puVar1 = *(ushort **)(unaff_A4 + -0x3eb0);
      iVar9 = (uint)*puVar1 * (uVar7 & 0xffff);
      uVar13 = unaff_D3w - uVar11;
      if ((short)uVar13 < 0) {
        uVar13 = -uVar13;
      }
      uVar12 = unaff_D2w - uVar10;
      if ((short)uVar12 < 0) {
        uVar12 = -uVar12;
      }
      uVar8 = uVar12;
      uVar5 = uVar13;
      if ((short)uVar13 < (short)uVar12) {
        uVar8 = uVar13;
        uVar5 = uVar12;
      }
      uVar11 = (ushort)*(byte *)(unaff_A4 + -0x4652 +
                                (int)(short)(ushort)(byte)(((unaff_D3w < uVar11) * '\x02' +
                                                           (unaff_D2w < uVar10)) * '\x02' +
                                                          (uVar13 < uVar12)));
      sVar3 = uVar8 * 2;
      uVar13 = (ushort)*(byte *)((int)puVar1 + 5);
      puVar16 = puVar1 + 4;
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        bVar2 = *(byte *)(unaff_A6 + 2);
        while ((bVar2 & 0x40) != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
        }
        puVar15 = puVar16 + 2;
        iVar17 = *(int *)puVar16;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x44) = 0xffff;
        *(ushort *)(unaff_A6 + 0x40) = uVar10 << 0xc | 0xbca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0x8000;
        uVar6 = uVar14 & 1;
        uVar14 = uVar14 >> 1;
        if (uVar6 == 0) {
          *(undefined2 *)(unaff_A6 + 0x72) = 0;
        }
        uVar12 = *(ushort *)(unaff_A4 + -0x3052);
        *(ushort *)(unaff_A4 + -0x3052) = uVar12 >> 1;
        puVar16 = puVar15;
        if ((uVar12 & 1) != 0) {
          *(short *)(unaff_A6 + 0x62) = sVar3;
          uVar12 = uVar11;
          if (sVar3 < (short)uVar5) {
            uVar12 = uVar11 | 0x40;
          }
          *(ushort *)(unaff_A6 + 0x52) = sVar3 - uVar5;
          *(ushort *)(unaff_A6 + 100) = (sVar3 - uVar5) - uVar5;
          *(ushort *)(unaff_A6 + 0x42) = uVar12;
          iVar17 = CONCAT22((short)((uint)iVar9 >> 0x10),(uVar10 >> 4) * 2 + (short)iVar9) + iVar17;
          *(int *)(unaff_A6 + 0x48) = iVar17;
          *(int *)(unaff_A6 + 0x54) = iVar17;
          *(ushort *)(unaff_A6 + 0x60) = *puVar1;
          *(ushort *)(unaff_A6 + 0x66) = *puVar1;
          *(ushort *)(unaff_A6 + 0x58) = (uVar5 + 1) * 0x40 + 2;
        }
      }
      return CONCAT44(in_D0,in_D1);
    }
    if ((uStack_34._2_2_ & uStack_34._0_2_) != 0) break;
    sVar3 = unaff_D2w - uVar10;
    sVar4 = unaff_D3w - uVar11;
    if (uStack_34._0_2_ == 0) {
      if ((uStack_34 & 8) == 0) {
        if ((uStack_34 & 4) == 0) {
          if ((uStack_34 & 2) == 0) {
            if ((uStack_34 & 1) != 0) {
              if (sVar3 != 0) {
                unaff_D2w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x469a) - unaff_D3w) *
                                    (int)sVar3) / (int)sVar4) + unaff_D2w;
              }
              unaff_D3w = *(ushort *)(unaff_A4 + -0x469a);
            }
          }
          else {
            if (sVar3 != 0) {
              unaff_D2w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x46a2) - unaff_D3w) *
                                  (int)sVar3) / (int)sVar4) + unaff_D2w;
            }
            unaff_D3w = *(ushort *)(unaff_A4 + -0x46a2);
          }
        }
        else {
          if (sVar4 != 0) {
            unaff_D3w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x4698) - unaff_D2w) *
                                (int)sVar4) / (int)sVar3) + unaff_D3w;
          }
          unaff_D2w = *(ushort *)(unaff_A4 + -0x4698);
        }
      }
      else {
        if (sVar4 != 0) {
          unaff_D3w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x469e) - unaff_D2w) * (int)sVar4
                              ) / (int)sVar3) + unaff_D3w;
        }
        unaff_D2w = *(ushort *)(unaff_A4 + -0x469e);
      }
      uVar10 = 10;
      if ((*(short *)(unaff_A4 + -0x469e) <= (short)unaff_D2w) &&
         (uVar10 = 2, *(short *)(unaff_A4 + -0x4698) < (short)unaff_D2w)) {
        uVar10 = 6;
      }
      if ((*(short *)(unaff_A4 + -0x46a2) <= (short)unaff_D3w) &&
         (uVar10 = uVar10 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)unaff_D3w)) {
        uVar10 = uVar10 | 1;
      }
      uStack_34 = (uint)uVar10;
    }
    else {
      if ((uStack_34 & 0x80000) == 0) {
        if ((uStack_34 & 0x40000) == 0) {
          if ((uStack_34 & 0x20000) == 0) {
            if ((uStack_34 & 0x10000) != 0) {
              if (sVar3 != 0) {
                uVar6 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x469a) - uVar11
                                                            ) * (int)sVar3) / (int)sVar4) + uVar10);
              }
              uVar7 = (uint)*(ushort *)(unaff_A4 + -0x469a);
            }
          }
          else {
            if (sVar3 != 0) {
              uVar6 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x46a2) - uVar11)
                                             * (int)sVar3) / (int)sVar4) + uVar10);
            }
            uVar7 = (uint)*(ushort *)(unaff_A4 + -0x46a2);
          }
        }
        else {
          if (sVar4 != 0) {
            uVar7 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x4698) - uVar10) *
                                           (int)sVar4) / (int)sVar3) + uVar11);
          }
          uVar6 = (uint)*(ushort *)(unaff_A4 + -0x4698);
        }
      }
      else {
        if (sVar4 != 0) {
          uVar7 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x469e) - uVar10) *
                                         (int)sVar4) / (int)sVar3) + uVar11);
        }
        uVar6 = (uint)*(ushort *)(unaff_A4 + -0x469e);
      }
      uVar10 = 10;
      if ((*(short *)(unaff_A4 + -0x469e) <= (short)uVar6) &&
         (uVar10 = 2, *(short *)(unaff_A4 + -0x4698) < (short)uVar6)) {
        uVar10 = 6;
      }
      if ((*(short *)(unaff_A4 + -0x46a2) <= (short)uVar7) &&
         (uVar10 = uVar10 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)uVar7)) {
        uVar10 = uVar10 | 1;
      }
      uStack_34 = CONCAT22(uVar10,uStack_34._2_2_);
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_000215d8 @ 000232ce ====

undefined2 thunk_FUN_000215d8(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x42cc) = param_1;
  uVar1 = FUN_000216b2(&LAB_00021608,param_2,&stack0x0000000c);
  **(undefined1 **)(unaff_A4 + -0x42cc) = 0;
  return uVar1;
}


// ==== thunk_FUN_00021dce @ 000232d4 ====

void thunk_FUN_00021dce(void)

{
  FUN_00021de2();
  return;
}


// ==== thunk_FUN_00021e02 @ 000232da ====

char * thunk_FUN_00021e02(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  do {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  return param_1;
}


// ==== thunk_FUN_00021e12 @ 000232e0 ====

char * thunk_FUN_00021e12(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = param_1;
  do {
    pcVar2 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar2;
  } while (cVar1 != '\0');
  return pcVar2 + (-1 - (int)param_1);
}


// ==== thunk_FUN_00021e82 @ 000232e6 ====

byte thunk_FUN_00021e82(undefined4 param_1)

{
  if ((0x40 < param_1._1_1_) && (param_1._1_1_ < 0x5b)) {
    param_1._1_1_ = param_1._1_1_ + 0x20;
  }
  return param_1._1_1_;
}


// ==== thunk_FUN_00021e9a @ 000232ec ====

undefined4 thunk_FUN_00021e9a(byte *param_1,byte *param_2)

{
  byte bVar1;
  short sVar2;
  
  sVar2 = 0x7ffe;
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    if (*param_1 != bVar1) {
      if (*param_1 <= bVar1) {
        return 0xffffffff;
      }
      return 1;
    }
  } while ((*param_1 != 0) && (sVar2 = sVar2 + -1, param_1 = param_1 + 1, sVar2 != -1));
  return 0;
}


// ==== thunk_FUN_00021eca @ 000232f2 ====

void thunk_FUN_00021eca(undefined1 *param_1,undefined1 *param_2,undefined4 param_3)

{
  if (param_2 == param_1) {
    return;
  }
  if (param_2 <= param_1) {
    while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    return;
  }
  param_1 = param_1 + param_3._0_2_;
  param_2 = param_2 + param_3._0_2_;
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    param_1 = param_1 + -1;
    param_2 = param_2 + -1;
    *param_2 = *param_1;
  }
  return;
}


// ==== thunk_FUN_00021ef4 @ 000232f8 ====

undefined4 thunk_FUN_00021ef4(char *param_1)

{
  short sVar2;
  undefined4 uVar1;
  
  do {
    if (*param_1 == '\0') {
      uVar1 = FUN_00022474();
      return uVar1;
    }
    param_1 = param_1 + 1;
    sVar2 = FUN_00022474();
  } while (sVar2 != -1);
  return 0xffffffff;
}


// ==== thunk_FUN_00021f2e @ 000232fe ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_00021f2e(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  short sVar4;
  undefined4 extraout_A0;
  undefined4 *puVar5;
  int unaff_A4;
  
  uVar2 = FUN_00021fa0();
  sVar4 = 0x4e3;
  puVar5 = (undefined4 *)(unaff_A4 + -0x439e);
  do {
    *puVar5 = 0;
    sVar4 = sVar4 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar4 != -1);
  *(BADSPACEBASE **)(unaff_A4 + -0x304c) = register0x0000003c;
  iVar1 = _DAT_00000004;
  *(int *)(unaff_A4 + -0x408a) = _DAT_00000004;
  if ((*(byte *)(iVar1 + 0x129) & 0x10) != 0) {
    (**(code **)(iVar1 + -0x1e))(uVar2,extraout_A0);
  }
  iVar3 = (**(code **)(iVar1 + -0x198))();
  *(int *)(unaff_A4 + -0x40e0) = iVar3;
  if (iVar3 == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== thunk_FUN_000222a8 @ 00023304 ====

char * thunk_FUN_000222a8(char *param_1,char *param_2)

{
  char cVar1;
  short sVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = param_1;
  do {
    pcVar4 = pcVar3;
    pcVar3 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  sVar2 = 0x7ffe;
  do {
    cVar1 = *param_2;
    pcVar3 = pcVar4 + 1;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') break;
    sVar2 = sVar2 + -1;
    pcVar4 = pcVar3;
    param_2 = param_2 + 1;
  } while (sVar2 != -1);
  if (cVar1 != '\0') {
    *pcVar3 = '\0';
  }
  return param_1;
}


// ==== thunk_FUN_000222d2 @ 0002330a ====

char * thunk_FUN_000222d2(char *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  
  bVar3 = param_3._0_2_ == 0;
  pcVar2 = param_1;
  while ((!bVar3 && (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1))) {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    bVar3 = cVar1 == '\0';
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  }
  if (!bVar3) {
    param_3._0_2_ = param_3._0_2_ + 1;
  }
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    *pcVar2 = '\0';
    pcVar2 = pcVar2 + 1;
  }
  return param_1;
}


// ==== thunk_FUN_000223cc @ 00023310 ====

undefined8 thunk_FUN_000223cc(void)

{
  int iVar1;
  int in_D0;
  int in_D1;
  bool bVar2;
  
  bVar2 = in_D0 < 0;
  if (in_D1 < 0) {
    bVar2 = !bVar2;
  }
  iVar1 = FUN_00022424();
  if (bVar2) {
    iVar1 = -iVar1;
  }
  return CONCAT44(iVar1,in_D1);
}


// ==== thunk_FUN_00022ab2 @ 00023316 ====

void thunk_FUN_00022ab2(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022aba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x24))();
  return;
}


// ==== thunk_FUN_00022ace @ 0002331c ====

void thunk_FUN_00022ace(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ad6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x48))();
  return;
}


// ==== thunk_FUN_00022ade @ 00023322 ====

void thunk_FUN_00022ade(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x66))();
  return;
}


// ==== thunk_FUN_00022aec @ 00023328 ====

void thunk_FUN_00022aec(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022af6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x6c))();
  return;
}


// ==== thunk_FUN_00022b06 @ 0002332e ====

void thunk_FUN_00022b06(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x84))();
  return;
}


// ==== thunk_FUN_00022b1e @ 00023334 ====

void thunk_FUN_00022b1e(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x54))();
  return;
}


// ==== thunk_FUN_00022b30 @ 0002333a ====

void thunk_FUN_00022b30(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x1e))();
  return;
}


// ==== thunk_FUN_00022b42 @ 00023340 ====

void thunk_FUN_00022b42(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x2a))();
  return;
}


// ==== thunk_FUN_00022b54 @ 00023346 ====

void thunk_FUN_00022b54(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x5a))();
  return;
}


// ==== thunk_FUN_00021d6e @ 0002334c ====

void thunk_FUN_00021d6e(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00021d78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x30))();
  return;
}


// ==== thunk_FUN_00022d48 @ 00023352 ====

void thunk_FUN_00022d48(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022d4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x78))();
  return;
}


// ==== thunk_FUN_00022d66 @ 00023358 ====

void thunk_FUN_00022d66(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022d6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x7e))();
  return;
}


// ==== thunk_FUN_00022e0c @ 0002335e ====

void thunk_FUN_00022e0c(void)

{
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x1e))();
  return;
}


// ==== thunk_FUN_00022e2e @ 00023364 ====

void thunk_FUN_00022e2e(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -300))();
  return;
}


// ==== thunk_FUN_00022e48 @ 0002336a ====

void thunk_FUN_00022e48(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e56. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0xf6))();
  return;
}


// ==== thunk_FUN_00022e5a @ 00023370 ====

void thunk_FUN_00022e5a(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x186))();
  return;
}


// ==== thunk_FUN_00022e6c @ 00023376 ====

void thunk_FUN_00022e6c(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0xc6))();
  return;
}


// ==== thunk_FUN_00022e78 @ 0002337c ====

void thunk_FUN_00022e78(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e86. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0xf0))();
  return;
}


// ==== thunk_FUN_00022e92 @ 00023382 ====

void thunk_FUN_00022e92(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ea0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x132))();
  return;
}


// ==== thunk_FUN_00022ea4 @ 00023388 ====

void thunk_FUN_00022ea4(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022eb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x156))();
  return;
}


// ==== thunk_FUN_00022eb4 @ 0002338e ====

void thunk_FUN_00022eb4(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ec0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x15c))();
  return;
}


// ==== thunk_FUN_00022ec4 @ 00023394 ====

void thunk_FUN_00022ec4(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x162))();
  return;
}


// ==== thunk_FUN_00022ed4 @ 0002339a ====

void thunk_FUN_00022ed4(void)

{
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x3c))();
  return;
}


// ==== thunk_FUN_00022eee @ 000233a0 ====

void thunk_FUN_00022eee(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ef2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x10e))();
  return;
}


