#pragma once

/**
 * \file burutter.h
 * \brief Declarations for the rumble/vibration motor control.
 *
 * Issues rumble (vibration) motor commands through the "BURUTTER" vibration
 * driver, controlling the big (strong) and small (weak) motors of the
 * DualShock controller.
 */

/* Decompiled globals (previously generated in src/_gen) */

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Issues a full-strength big (strong) motor vibration.
 *
 * Initializes the BURUTTER driver on first use; if vibration is enabled,
 * sends a full-strength (0xFFFF) big-motor command via the driver.
 *
 * \return Non-zero on success (DeviceIoControl result), 0 if vibration is
 *         disabled.
 */
int joy_issue_big_motor();
/**
 * \brief Issues a small (weak) motor vibration.
 *
 * Initializes the BURUTTER driver on first use; if vibration is enabled,
 * sends a small-motor command via the driver.
 *
 * \return Non-zero on success (DeviceIoControl result), 0 if vibration is
 *         disabled.
 */
int joy_issue_small_motor();
