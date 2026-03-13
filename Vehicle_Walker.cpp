#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "../Game_local.h"
#include "VehicleAnimated.h"

class rvVehicleWalker : public rvVehicleAnimated {
public:

	CLASS_PROTOTYPE( rvVehicleWalker );

	rvVehicleWalker ( void );
	
	void				Think					( void );
	void				Spawn					( void );
	void				Save					( idSaveGame *savefile ) const;
	void				Restore					( idRestoreGame *savefile );

	virtual void		UpdateState				( void );
	virtual void		SetInput				( int position, const usercmd_t& cmd, const idAngles& newAngles );

	const char*			stopAnimName;

	virtual bool		FindClearExitPoint		( int pos, idVec3& origin, idMat3& axis ) const;

private:
	void				HandleStrafing			( void );

	// AC void variables for Movement
	void				ACInit(void);
	void				ACMechanic(void);
	void				ACQuickBoostManage(void);
	void				ACAssaultBoostManage(void);
	void				ACFlightManage(void);
	void				ACQuickTurnManage(void);
	void				ACFasterMovement(void);

	// AC Quick Boost variables (dash to the left/right)
	bool				ac_activeQuickBoost;
	int					ac_startQuickBoost;
	int					ac_cooldownendQuickBoost;
	idVec3				ac_directionQuickBoost;
	float				ac_speedQuickBoost;
	int					ac_durationQuickBoost;
	int					ac_cooldownQuickBoost;

	// AC Assault Boost variables (rapid charge attack at the front)
	bool				ac_activeAssaultBoost;
	int					ac_startAssaultBoost;
	float				ac_speedAssaultBoost;
	float				ac_energyAssaultBoost;
	float				ac_maxAssaultBoost;
	float				ac_drainAssaultBoost;
	float				ac_regenAssaultBoost;

	// AC Flight variables (walker flies up and down)
	bool				ac_Flying;
	float				ac_energyFlight;
	float				ac_maxFlight;
	float				ac_thrustFlight;
	float				ac_drainFlight;
	float				ac_regenFlight;
	int					ac_timeFlight;

	// AC Quick Turn variables (rapid  180 degree turn)
	bool				ac_activeQuickTurn;
	int					ac_startQuickTurn;
	float				ac_yawQuickTurn;
	float				ac_targetQuickTurn;
	int					ac_durationQuickTurn;
	int					ac_cooldownQuickTurn;

	float				ac_fasterMovement;

	// AC Input tracking variables (input tracking done through common->KeyState())
	bool				ac_holdShift;
	bool				ac_holdFlyUp;
	bool				ac_holdFlyDown;
	bool				ac_holdTurnLeft;
	bool				ac_holdTurnRight;
	bool				ac_prevholdShift;
	bool				ac_prevholdFlyUp;
	bool				ac_prevholdFlyDown;
	bool				ac_prevholdTurnLeft;
	bool				ac_prevholdTurnRight;
	byte				ac_lastImpulse;
	bool				ac_prevHasDriver;
	bool				ac_prevholdLoadoutLMB;
	bool				ac_pressedMoveUp;
	bool				ac_pendingLoadoutLMB;

	// AC6 Pile Bunker variable, which is set in the UpdateState when slot 8 is fired and used in the AC6_HandlePileBunker function below
	bool				ac_firedPileBunker;

	void				ACPileBunkerManage(void);

	// AC Weapon Loadout Functions
	void				ACInitWeaponMenu(void);
	void				ACToggleWeaponMenu(void);
	void				ACWeaponLoadoutManage(void);
	void				ACApplyWeaponMenu(void);
	void				ACUpdateWeaponMenu(void);
	void				ACShoulderWeaponMenuManage(void);
	void				ACArmWeaponMenuManage(void);

	// 4 Weapon Slots categories and their variables (Arm Left, Arm Right, Shoulder Left, Shoulder Right) used with an assigned num value: 0 = Arm L, 1 = Arm R, 2 = Shoulder L, 3 = Shoulder R
	idStr				ac_slotsWeaponMenu[4];
	bool				ac_openWeaponMenu;
	int					ac_slotcursorWeaponMenu;
	int					ac_cursorWeaponMenu;												// From 0-3, checks which slot row is currently highlighted for the cursor
	bool				ac_slotselectedWeaponMenu;	// From 0-9, checks which weapon row is highlighted through inputting the num value assigned to the weapon
	int					ac_activeslotArmWeaponMenu;			// Either 0 or 1, checks which Arm weapons are active in mWeapons
	int					ac_activeslotShoulderWeaponMenu;			// Either 2 or 3, checks which Shoulder weapons are active in mWeapons
	bool				ac_holdShoulderFire;			
	bool				ac_togglependingWeaponMenu;	
	bool				ac_togglepressedWeaponMenu;
	bool				ac_justpressedFireWeaponMenu;
	bool				ac_NavUpWeaponMenu;
	bool				ac_NavDownWeaponMenu;
	bool				ac_inWeaponColumnWeaponMenu;
	bool				ac_holdArmFire;
	bool				ac_scrollupPendingWeaponMenu;
	bool				ac_scrolldownPendingWeaponMenu;
	bool 				ac_pendingRMBWeaponMenu;
	bool 				ac_prevholdRMBWeaponMenu;
	//bool				ac_numkeyPendingWeaponMenu;

	static const char* ACWEAPONSDEFS[10];
	static const char* ACWEAPONSNAMES[10];

	stateResult_t		Frame_ForwardRight		( int );
	stateResult_t		Frame_ForwardLeft		( int );
	stateResult_t		Frame_BackwardRight		( int );
	stateResult_t		Frame_BackwardLeft		( int );

	stateResult_t		State_Wait_OnlineAnim	( const stateParms_t& parms );

	stateResult_t		State_Idle				( const stateParms_t& parms );
	stateResult_t		State_IdleThink			( const stateParms_t& parms );
	stateResult_t		State_IdleOffline		( const stateParms_t& parms );
	stateResult_t		State_Offline			( const stateParms_t& parms );
	stateResult_t		State_Online			( const stateParms_t& parms );

	stateResult_t		State_ForwardStart		( const stateParms_t& parms );
	stateResult_t		State_Forward			( const stateParms_t& parms );
	stateResult_t		State_BackwardStart		( const stateParms_t& parms );
	stateResult_t		State_Backward			( const stateParms_t& parms );
	stateResult_t		State_Stop				( const stateParms_t& parms );
	stateResult_t		State_Turn				( const stateParms_t& parms );
	stateResult_t		State_TurnThink			( const stateParms_t& parms );
	stateResult_t		State_ScriptedAnim		( const stateParms_t& parms );

	void				Event_ScriptedAnim		( const char* animname, int blendFrames, bool loop, bool endWithIdle );
	void 				Event_ScriptedDone		( void );
	void				Event_ScriptedStop		( void );

	CLASS_STATES_PROTOTYPE ( rvVehicleWalker );
};

CLASS_DECLARATION( rvVehicleAnimated, rvVehicleWalker )
	EVENT( AI_ScriptedAnim,	rvVehicleWalker::Event_ScriptedAnim )
	EVENT( AI_ScriptedDone,	rvVehicleWalker::Event_ScriptedDone )
	EVENT( AI_ScriptedStop,	rvVehicleWalker::Event_ScriptedStop )
END_CLASS

const char* rvVehicleWalker::ACWEAPONSDEFS[10] = {
	"ac_weapon_handgun",
	"ac_weapon_machinegun",
	"ac_weapon_stunneedle",
	"ac_weapon_pulseshield",
	"ac_weapon_bazooka",
	"ac_weapon_laserturret",
	"ac_weapon_lightwave",
	"ac_weapon_gatling",
	"ac_weapon_pilebunker",
	"ac_weapon_needlegun"
};

const char* rvVehicleWalker::ACWEAPONSNAMES[10] = {
	"Handgun",
	"Machine Gun",
	"Stun Needle",
	"Pulse Shield",
	"Bazooka",
	"Laser Turret",
	"Light Wave",
	"Gatling",
	"Pile Bunker",
	"Needle Gun"
};

/*
================
rvVehicleWalker::rvVehicleWalker
================
*/
rvVehicleWalker::rvVehicleWalker ( void ) {
	stopAnimName = "";
	ACInit();
}

/*
================
rvVehicleWalker::Think
================
*/
void rvVehicleWalker::Think ( void ) {

	bool hasDriver = HasDrivers() && !IsStalled();

	// Auto-open the weapon menu right away when a driver enters the walker
	if (hasDriver && !ac_prevHasDriver) {
		
		ac_openWeaponMenu = false;
		
		//ac_cursorWeaponMenu = 0;
		
		ACToggleWeaponMenu();
	}
	ac_prevHasDriver = hasDriver;

	if (hasDriver) {
		ACMechanic();
	}

	rvVehicleAnimated::Think();

	if ( !HasDrivers() || IsStalled() ) {
		return;
	}

	idVec3 delta;
	animator.GetDelta( gameLocal.time - gameLocal.GetMSec(), gameLocal.time, delta );

	if ( delta.LengthSqr() > 0.1f ) {
		gameLocal.RadiusDamage( GetOrigin(), this, this, this, this, spawnArgs.GetString( "def_stompDamage", "damage_Smallexplosion" ) );
	}
}

/*
================
rvVehicleWalker::Spawn
================
*/
void rvVehicleWalker::Spawn	( void ) {

	ac_speedQuickBoost = spawnArgs.GetFloat("ac_quickBoostSpeed", "1200");
	ac_durationQuickBoost = spawnArgs.GetInt("ac_quickBoostDuration", "1000");
	ac_cooldownQuickBoost = spawnArgs.GetInt("ac_quickBoostCooldown", "400");

	ac_speedAssaultBoost = spawnArgs.GetFloat("ac_assaultBoostSpeed", "1500");
	ac_maxAssaultBoost = spawnArgs.GetFloat("ac_assaultBoostMaxEnergy", "100");
	ac_energyAssaultBoost = ac_maxAssaultBoost;
	ac_drainAssaultBoost = spawnArgs.GetFloat("ac_assaultBoostDrain", "25");
	ac_regenAssaultBoost = spawnArgs.GetFloat("ac_assaultBoostRegen", "15");

	ac_maxFlight = spawnArgs.GetFloat("ac_flightMaxEnergy", "100");
	ac_energyFlight = ac_maxFlight;
	ac_thrustFlight = spawnArgs.GetFloat("ac_flightThrustForce", "1200");
	ac_drainFlight = spawnArgs.GetFloat("ac_flightEnergyDrain", "30");
	ac_regenFlight = spawnArgs.GetFloat("ac_flightEnergyRegen", "20");

	ac_durationQuickTurn = spawnArgs.GetInt("ac_quickTurnDuration", "1000");

	ac_fasterMovement = spawnArgs.GetFloat("ac_baseSpeedMultiplier", "1.5");

	ACApplyWeaponMenu();

	SetAnimState ( ANIMCHANNEL_LEGS, "State_IdleOffline", 0 );
}

/*
================
rvVehicleWalker::Save
================
*/
void rvVehicleWalker::Save ( idSaveGame *savefile ) const {
	savefile->WriteString( stopAnimName );

	savefile->WriteBool(ac_activeQuickBoost);
	savefile->WriteInt(ac_startQuickBoost);
	savefile->WriteInt(ac_cooldownendQuickBoost);
	savefile->WriteVec3(ac_directionQuickBoost);
	savefile->WriteFloat(ac_speedQuickBoost);
	savefile->WriteInt(ac_durationQuickBoost);
	savefile->WriteInt(ac_cooldownQuickBoost);

	savefile->WriteBool(ac_activeAssaultBoost);
	savefile->WriteInt(ac_startAssaultBoost);
	savefile->WriteFloat(ac_speedAssaultBoost);
	savefile->WriteFloat(ac_energyAssaultBoost);
	savefile->WriteFloat(ac_maxAssaultBoost);
	savefile->WriteFloat(ac_drainAssaultBoost);
	savefile->WriteFloat(ac_regenAssaultBoost);

	savefile->WriteBool(ac_Flying);
	savefile->WriteFloat(ac_energyFlight);
	savefile->WriteFloat(ac_maxFlight);
	savefile->WriteFloat(ac_thrustFlight);
	savefile->WriteFloat(ac_drainFlight);
	savefile->WriteFloat(ac_regenFlight);
	savefile->WriteInt(ac_timeFlight);

	savefile->WriteBool(ac_activeQuickTurn);
	savefile->WriteInt(ac_startQuickTurn);
	savefile->WriteFloat(ac_yawQuickTurn);
	savefile->WriteFloat(ac_targetQuickTurn);
	savefile->WriteInt(ac_durationQuickTurn);
	savefile->WriteInt(ac_cooldownQuickTurn);

	savefile->WriteFloat(ac_fasterMovement);

	// weapon menu state
	for (int i = 0; i < 4; i++) {
		savefile->WriteString(ac_slotsWeaponMenu[i]);
	}
	savefile->WriteInt(ac_activeslotArmWeaponMenu);
	savefile->WriteInt(ac_activeslotShoulderWeaponMenu);
}

/*
================
rvVehicleWalker::Restore
================
*/
void rvVehicleWalker::Restore ( idRestoreGame *savefile ) {
	//twhitaker: I just happened to see this, while going through this code which I originally wrote (at 3am or so).
	//TODO: fix this.  Make stopAnimName an idStr?
	idStr str;
	savefile->ReadString( str );
	stopAnimName = str;

	savefile->ReadBool(ac_activeQuickBoost);
	savefile->ReadInt(ac_startQuickBoost);
	savefile->ReadInt(ac_cooldownendQuickBoost);
	savefile->ReadVec3(ac_directionQuickBoost);
	savefile->ReadFloat(ac_speedQuickBoost);
	savefile->ReadInt(ac_durationQuickBoost);
	savefile->ReadInt(ac_cooldownQuickBoost);

	savefile->ReadBool(ac_activeAssaultBoost);
	savefile->ReadInt(ac_startAssaultBoost);
	savefile->ReadFloat(ac_speedAssaultBoost);
	savefile->ReadFloat(ac_energyAssaultBoost);
	savefile->ReadFloat(ac_maxAssaultBoost);
	savefile->ReadFloat(ac_drainAssaultBoost);
	savefile->ReadFloat(ac_regenAssaultBoost);

	savefile->ReadBool(ac_Flying);
	savefile->ReadFloat(ac_energyFlight);
	savefile->ReadFloat(ac_maxFlight);
	savefile->ReadFloat(ac_thrustFlight);
	savefile->ReadFloat(ac_drainFlight);
	savefile->ReadFloat(ac_regenFlight);
	savefile->ReadInt(ac_timeFlight);

	savefile->ReadBool(ac_activeQuickTurn);
	savefile->ReadInt(ac_startQuickTurn);
	savefile->ReadFloat(ac_yawQuickTurn);
	savefile->ReadFloat(ac_targetQuickTurn);
	savefile->ReadInt(ac_durationQuickTurn);
	savefile->ReadInt(ac_cooldownQuickTurn);

	savefile->ReadFloat(ac_fasterMovement);

	// weapon menu state for restore
	for (int i = 0; i < 4; i++) {
		savefile->ReadString(ac_slotsWeaponMenu[i]);
	}
	savefile->ReadInt(ac_activeslotArmWeaponMenu);
	savefile->ReadInt(ac_activeslotShoulderWeaponMenu);

	ACApplyWeaponMenu();

	ac_holdShift = false;
	ac_holdFlyUp = false;
	ac_holdFlyDown = false;
	ac_holdTurnLeft = false;
	ac_holdTurnRight = false;
	ac_prevholdShift = false;
	ac_prevholdFlyUp = false;
	ac_prevholdFlyDown = false;
	ac_prevholdTurnLeft = false;
	ac_prevholdTurnRight = false;
	ac_lastImpulse = 0;
	ac_prevHasDriver = false;
	ac_pressedMoveUp = false;
	ac_openWeaponMenu = false;
	ac_holdShoulderFire = false;
	ac_togglependingWeaponMenu = false;
	ac_togglepressedWeaponMenu = false;
	ac_justpressedFireWeaponMenu = false;
	ac_NavUpWeaponMenu = false;
	ac_NavDownWeaponMenu = false;
	ac_inWeaponColumnWeaponMenu = false;
	ac_prevholdLoadoutLMB = false;
	ac_pendingLoadoutLMB = false;
	ac_holdArmFire = false;
	ac_scrollupPendingWeaponMenu = false;
	ac_scrolldownPendingWeaponMenu = false;
	ac_pendingRMBWeaponMenu = false;
	ac_prevholdRMBWeaponMenu = false;
	//ac_numkeyPendingWeaponMenu = -1;
	ac_slotcursorWeaponMenu = 0;
	ac_slotselectedWeaponMenu = false;
	ac_cursorWeaponMenu = 0;
}

/*
================
rvVehicleWalker::UpdateState
================
*/
void rvVehicleWalker::UpdateState ( void ) {
	rvVehiclePosition& pos = positions[0];
	usercmd_t& cmd	= pos.mInputCmd;

	vfl.driver		= pos.IsOccupied();
  	vfl.forward		= (vfl.driver && cmd.forwardmove > 0);
  	vfl.backward	= (vfl.driver && cmd.forwardmove < 0);
  	vfl.right		= (vfl.driver && cmd.rightmove < 0);
  	vfl.left		= (vfl.driver && cmd.rightmove > 0);	
	vfl.strafe		= (vfl.driver && cmd.buttons & BUTTON_STRAFE );

	if ( g_vehicleMode.GetInteger() != 0 ) {
		vfl.strafe = !vfl.strafe;
	}

	ac_prevholdShift = ac_holdShift;
	ac_prevholdFlyUp = ac_holdFlyUp;
	ac_prevholdFlyDown = ac_holdFlyDown;
	ac_prevholdTurnLeft = ac_holdTurnLeft;
	ac_prevholdTurnRight = ac_holdTurnRight;

	if (vfl.driver) {
		bool alwaysRun = cvarSystem->GetCVarBool("in_alwaysRun");
		bool runBit = (cmd.buttons & BUTTON_RUN) != 0;
		ac_holdShift = alwaysRun ? !runBit : runBit;
		ac_holdFlyUp = ac_pressedMoveUp;
		ac_holdFlyDown = (cmd.upmove < 0);

		ac_holdTurnLeft = (cmd.buttons & BUTTON_VOICECHAT) != 0;
		ac_holdTurnRight = (cmd.buttons & BUTTON_TOURNEY) != 0;

		{
			rvVehiclePosition* wp = &positions[0];
			int cw = wp->mCurrentWeapon;
			rvVehicleWeapon* activeWpn = (cw >= 0 && cw < wp->mWeapons.Num())
				? static_cast<rvVehicleWeapon*>(wp->mWeapons[cw]) : NULL;
			(void)activeWpn; 
			// Check the Arm's active slot from weapon menu name for pile bunker
			ac_firedPileBunker = (idStr::Icmp(ac_slotsWeaponMenu[ac_activeslotArmWeaponMenu], "ac_weapon_pilebunker") == 0
				|| idStr::Icmp(ac_slotsWeaponMenu[ac_activeslotShoulderWeaponMenu], "ac_weapon_pilebunker") == 0)
				&& (cmd.buttons & BUTTON_ATTACK);
		}

		ac_holdShoulderFire = (cmd.buttons & BUTTON_ZOOM) != 0 && !ac_activeQuickTurn;

		ac_togglepressedWeaponMenu = ac_togglependingWeaponMenu;
		ac_togglependingWeaponMenu = false;

		ac_NavUpWeaponMenu = ac_scrollupPendingWeaponMenu;
		ac_NavDownWeaponMenu = ac_scrolldownPendingWeaponMenu;
		ac_scrollupPendingWeaponMenu = false;
		ac_scrolldownPendingWeaponMenu = false;

		ac_justpressedFireWeaponMenu = ac_pendingLoadoutLMB;
		ac_pendingLoadoutLMB = false;

		ac_holdArmFire = (cmd.buttons & BUTTON_ATTACK) != 0 && !ac_openWeaponMenu;

	}

	else {
		ac_holdShift = false;
		ac_holdFlyUp = false;
		ac_holdFlyDown = false;
		ac_holdTurnLeft = false;
		ac_holdTurnRight = false;
		ac_firedPileBunker = false;
		ac_holdShoulderFire = false;
		ac_holdArmFire = false;
		ac_togglepressedWeaponMenu = false;
		ac_NavUpWeaponMenu = false;
		ac_NavDownWeaponMenu = false;
		ac_scrollupPendingWeaponMenu = false;
		ac_scrolldownPendingWeaponMenu = false;
		ac_justpressedFireWeaponMenu = false;
		ac_pendingRMBWeaponMenu = false;
		//ac_numkeyPendingWeaponMenu = -1;
	}
}

/*
================
rvVehicleWalker::SetInput
================
*/
void rvVehicleWalker::SetInput ( int position, const usercmd_t& cmd, const idAngles& newAngles ) {
	usercmd_t* pcmd = const_cast<usercmd_t*>( &cmd );
	pcmd->rightmove *= -1;

	ac_pressedMoveUp = (pcmd->upmove > 0);
	if (pcmd->upmove > 0) {
		pcmd->upmove = 0;
	}

	// AC6: Freezes all the movement while the weapon menu screen is open.
	if (ac_openWeaponMenu) {
		if (pcmd->forwardmove > 0) {
			ac_scrollupPendingWeaponMenu = true;
		}
		if (pcmd->forwardmove < 0) {
			ac_scrolldownPendingWeaponMenu = true;
		}
		pcmd->forwardmove = 0;
		pcmd->rightmove = 0;
		ac_pressedMoveUp = false;
	}

	{
		static bool prevIngameStats = false;
		bool curIngameStats = (pcmd->buttons & BUTTON_INGAMESTATS) != 0;
		if (curIngameStats && !prevIngameStats) {
			ac_togglependingWeaponMenu = true;
		}
		if (curIngameStats) {
			pcmd->buttons &= ~BUTTON_INGAMESTATS;
		}
		prevIngameStats = curIngameStats;
	}

	{
		bool lmbNow = (pcmd->buttons & BUTTON_ATTACK) != 0;
		if (ac_openWeaponMenu) {
			if (lmbNow && !ac_prevholdLoadoutLMB) {
				ac_pendingLoadoutLMB = true;
			}
			ac_prevholdLoadoutLMB = lmbNow;
			pcmd->buttons &= ~BUTTON_ATTACK;
		}
		else {
			ac_pendingLoadoutLMB = false;
			ac_prevholdLoadoutLMB = false;
		}
	}

	byte curSeq = pcmd->flags & UCF_IMPULSE_SEQUENCE;
	bool newImpulse = (curSeq != (ac_lastImpulse & UCF_IMPULSE_SEQUENCE));
	if (newImpulse) {
		ac_lastImpulse = pcmd->flags;
		if (pcmd->impulse == IMPULSE_23) { pcmd->buttons |= BUTTON_VOICECHAT; }
		if (pcmd->impulse == IMPULSE_25) { pcmd->buttons |= BUTTON_TOURNEY; }
		
		if (pcmd->impulse == 24) {
			ac_togglependingWeaponMenu = true;
			pcmd->impulse = 17; 
		}

		if (pcmd->impulse == IMPULSE_14 || pcmd->impulse == IMPULSE_15) {
			if (ac_openWeaponMenu) {
				if (pcmd->impulse == IMPULSE_15) { ac_scrollupPendingWeaponMenu = true; }
				if (pcmd->impulse == IMPULSE_14) { ac_scrolldownPendingWeaponMenu = true; }
			}
			pcmd->impulse = 17;
		}
		if (pcmd->impulse >= IMPULSE_0 && pcmd->impulse <= IMPULSE_12) {
			pcmd->impulse = 17; 
		}

	}

	{
		bool rmbNow = (pcmd->buttons & BUTTON_ZOOM) != 0;
		if (ac_openWeaponMenu) {
			if (rmbNow && !ac_prevholdRMBWeaponMenu) {
				ac_pendingRMBWeaponMenu = true;
			}
			ac_prevholdRMBWeaponMenu = rmbNow;
			pcmd->buttons &= ~BUTTON_ZOOM;
		}
		else {
			ac_pendingRMBWeaponMenu = false;
			ac_prevholdRMBWeaponMenu = false;
		}
	}

	GetPosition(position)->SetInput ( cmd, newAngles );
}

/*
================
rvVehicleWalker::HandleStrafing
================
*/
void rvVehicleWalker::HandleStrafing ( void ) {
	
	idVec3 strafeDelta = spawnArgs.GetVector("strafe_delta", "0 0 1.2");
	
	strafeDelta *= ac_fasterMovement;

	if (vfl.right) {
		additionalDelta -= strafeDelta;
	}
	if (vfl.left) {
		additionalDelta += strafeDelta;
	}
	
}

/*
================
rvVehicleWalker::ACInit
================
*/
void rvVehicleWalker::ACInit(void) {
	ac_activeQuickBoost = false;
	ac_startQuickBoost = 0;
	ac_cooldownendQuickBoost = 0;
	ac_directionQuickBoost.Zero();
	ac_speedQuickBoost = 1200.0f;
	ac_durationQuickBoost = 1000;
	ac_cooldownQuickBoost = 400;

	ac_activeAssaultBoost = false;
	ac_startAssaultBoost = 0;
	ac_speedAssaultBoost = 1500.0f;
	ac_energyAssaultBoost = 100.0f;
	ac_maxAssaultBoost = 100.0f;
	ac_drainAssaultBoost = 25.0f;
	ac_regenAssaultBoost = 15.0f;

	ac_Flying = false;
	ac_energyFlight = 100.0f;
	ac_maxFlight = 100.0f;
	ac_thrustFlight = 1200.0f;
	ac_drainFlight = 30.0f;
	ac_regenFlight = 20.0f;
	ac_timeFlight = 0;

	ac_activeQuickTurn = false;
	ac_startQuickTurn = 0;
	ac_yawQuickTurn = 0.0f;
	ac_targetQuickTurn = 0.0f;
	ac_durationQuickTurn = 1000;
	ac_cooldownQuickTurn = 0;

	ac_fasterMovement = 1.5f;

	ac_holdShift = false;
	ac_holdFlyUp = false;
	ac_holdFlyDown = false;
	ac_holdTurnLeft = false;
	ac_holdTurnRight = false;
	ac_prevholdShift = false;
	ac_prevholdFlyUp = false;
	ac_prevholdFlyDown = false;
	ac_prevholdTurnLeft = false;
	ac_prevholdTurnRight = false;
	ac_lastImpulse = 0;
	ac_firedPileBunker = false;
	ac_prevHasDriver = false;
	ac_pressedMoveUp = false;
	ac_scrollupPendingWeaponMenu = false;
	ac_scrolldownPendingWeaponMenu = false;
	ac_prevholdRMBWeaponMenu = false;
	ac_pendingRMBWeaponMenu = false;
	ac_holdArmFire = false;
	//ac_numkeyPendingWeaponMenu = -1;
	ac_cursorWeaponMenu = 0;

	ACInitWeaponMenu();
}

/*
================
rvVehicleWalker::ACInitWeaponMenu
  Initializes the weapon menu. By default, the menu will show Handgun, MG, Bazooka, Laser Turret for the Arm and Shoulder slots. Called from the constructor ACInit() and can be also be re-called after the Restore.
================
*/
void rvVehicleWalker::ACInitWeaponMenu(void) {
	ac_slotsWeaponMenu[0] = "ac_weapon_handgun";
	ac_slotsWeaponMenu[1] = "ac_weapon_machinegun";
	ac_slotsWeaponMenu[2] = "ac_weapon_bazooka";
	ac_slotsWeaponMenu[3] = "ac_weapon_laserturret";

	ac_openWeaponMenu = false;
	ac_slotcursorWeaponMenu = 0;
	ac_slotselectedWeaponMenu = false;
	ac_activeslotArmWeaponMenu = 0;
	ac_activeslotShoulderWeaponMenu = 2;
	ac_holdShoulderFire = false;
	ac_togglependingWeaponMenu = false;
	ac_togglepressedWeaponMenu = false;
	ac_justpressedFireWeaponMenu = false;
	ac_NavUpWeaponMenu = false;
	ac_NavDownWeaponMenu = false;
	ac_inWeaponColumnWeaponMenu = false;
	ac_prevholdLoadoutLMB = false;
	ac_pendingLoadoutLMB = false;
	ac_holdArmFire = false;
	ac_scrollupPendingWeaponMenu = false;
	ac_scrolldownPendingWeaponMenu = false;
	ac_pendingRMBWeaponMenu = false;
	//ac_numkeyPendingWeaponMenu = -1;
	ac_cursorWeaponMenu = 0;
}

/*
================
rvVehicleWalker::ACApplyWeaponMenu
  Swaps out the walker's weapon array to instead match the 2 Arm and 2 Shoulder slots for 4 loadout slots in total. Removes the current weapon instance and is redirected from the def names. It is also called at Spawn and for assigning a weapon slot.
================
*/
void rvVehicleWalker::ACApplyWeaponMenu(void) {
	rvVehiclePosition* pos = GetPosition(0);
	if (!pos) {
		return;
	}

	pos->mWeapons.DeleteContents(true);
	pos->mCurrentWeapon = 0;

	for (int i = 0; i < 4; i++) {
		const idDict* dict = gameLocal.FindEntityDefDict(ac_slotsWeaponMenu[i]);
		if (!dict) {
			gameLocal.Warning("ACApplyWeaponMenu: Unknown weapon def: '%s' in slot: %d",
				ac_slotsWeaponMenu[i].c_str(), i);
			continue;
		}
		idTypeInfo* typeInfo = idClass::GetClass(dict->GetString("spawnclass"));
		if (!typeInfo || !typeInfo->IsType(rvVehicleWeapon::GetClassType())) {
			gameLocal.Warning("ACApplyWeaponMenu: '%s' is not a rvVehicleWeapon",
				ac_slotsWeaponMenu[i].c_str());
			continue;
		}
		pos->AddPart(*typeInfo, *dict);
	}

	ac_activeslotArmWeaponMenu = 0;
	ac_activeslotShoulderWeaponMenu = 2;
	pos->mCurrentWeapon = ac_activeslotArmWeaponMenu;

	for (int i = 0; i < pos->mWeapons.Num(); i++) {
		pos->mWeapons[i]->Activate(true);
	}
}

/*
================
rvVehicleWalker::ACMechanic
  Acts as the primary AC6 movement function, its called every frame before the parent Think function and handles all the AC6 style movement mechanics.
================
*/
void rvVehicleWalker::ACMechanic(void) {
	ACQuickTurnManage();
	ACPileBunkerManage();
	ACQuickBoostManage();
	ACAssaultBoostManage();
	ACFlightManage();
	ACFasterMovement();
	ACShoulderWeaponMenuManage();
	ACArmWeaponMenuManage();
	ACWeaponLoadoutManage();
	ACUpdateWeaponMenu();
}

/*
================
rvVehicleWalker::ACPileBunkerManage
  When Pile Bunker is fired, it instantly triggers an Assault Boost so the walker sprints into the front to mimic the mechanic in AC6.
================
*/
void rvVehicleWalker::ACPileBunkerManage(void) {
	if (!ac_firedPileBunker) {
		return;
	}
	ac_firedPileBunker = false;

	if (ac_activeQuickBoost) {
		return;
	}

	ac_activeQuickBoost = true;
	ac_startQuickBoost = gameLocal.time;
	ac_directionQuickBoost = idVec3(1.0f, 0.0f, 0.0f); 
}

/*
================
rvVehicleWalker::ACShoulderWeaponMenuManage
  Fires the Shoulder weapon (which are in slots 2 and 3) when RMB is held/pressed.It's called every frame and is dependent upon ac_holdShoulderFire set in UpdateState().
================
*/
void rvVehicleWalker::ACShoulderWeaponMenuManage(void) {
	if (!ac_holdShoulderFire || ac_openWeaponMenu) {
		return;
	}
	rvVehiclePosition* pos = GetPosition(0);
	if (!pos) {
		return;
	}
	if (2 < pos->mWeapons.Num()) {
		static_cast<rvVehicleWeapon*>(pos->mWeapons[2])->Fire();
	}
	if (3 < pos->mWeapons.Num()) {
		static_cast<rvVehicleWeapon*>(pos->mWeapons[3])->Fire();
	}
}

/*
================
rvVehicleWalker::ACArmWeaponMenuManage
  Fires the arm slot 0 and 1 weapons when LMB is held/pressed.
================
*/
void rvVehicleWalker::ACArmWeaponMenuManage(void) {
	if (!ac_holdArmFire || ac_openWeaponMenu) {
		return;
	}
	rvVehiclePosition* pos = GetPosition(0);
	if (!pos) {
		return;
	}
	if (1 < pos->mWeapons.Num()) {
		static_cast<rvVehicleWeapon*>(pos->mWeapons[1])->Fire();
	}
	if (0 == pos->mWeapons.Num()) {
		static_cast<rvVehicleWeapon*>(pos->mWeapons[0])->Fire();
	}
}


/*
================
rvVehicleWalker::ACToggleWeaponMenu
  Open/close the weapon menu GUI.
================
*/
void rvVehicleWalker::ACToggleWeaponMenu(void) {
	ac_openWeaponMenu = !ac_openWeaponMenu;
	if (ac_openWeaponMenu) {
		
		ac_slotcursorWeaponMenu = 0;
		ac_slotselectedWeaponMenu = false;
		
		ac_cursorWeaponMenu = 0;	
	}
	idUserInterface* hud = GetHud();
	if (hud) {
		gameLocal.Warning("AC6 Weapon Menu: GetHud() == NULL (GUI unavailable)");
		return;
	}

	hud->HandleNamedEvent(ac_openWeaponMenu ? "openWeaponMenu" : "closeWeaponMenu");
}

/*
================
rvVehicleWalker::ACWeaponLoadoutManage
  Checks the weapon menu navigation and slot assignment logic every frame.
================
*/
void rvVehicleWalker::ACWeaponLoadoutManage(void) {
	if (ac_togglepressedWeaponMenu) {
		ACToggleWeaponMenu();
		return;
	}

	if (!ac_openWeaponMenu) {
		return;
	}

	static int lastNavTime = 0;
	bool canNavigate = (gameLocal.time - lastNavTime >= 100);

	if (!ac_slotselectedWeaponMenu) {

		if (ac_justpressedFireWeaponMenu) {
			ac_slotselectedWeaponMenu = true;
			ac_cursorWeaponMenu = 0;
		}

		if (canNavigate && ac_NavUpWeaponMenu) {
			ac_slotcursorWeaponMenu = (ac_slotcursorWeaponMenu + 3) % 4;
			lastNavTime = gameLocal.time;
		}
		if (canNavigate && ac_NavDownWeaponMenu) {
			ac_slotcursorWeaponMenu = (ac_slotcursorWeaponMenu + 3) % 4;
			lastNavTime = gameLocal.time;
		}
	}
	else {
		if (ac_justpressedFireWeaponMenu) {
			ac_slotsWeaponMenu[ac_slotcursorWeaponMenu] = ACWEAPONSDEFS[ac_cursorWeaponMenu];
			ACApplyWeaponMenu();
			ac_slotselectedWeaponMenu = false;
		}
		if (canNavigate && ac_NavUpWeaponMenu) {
			ac_cursorWeaponMenu = (ac_cursorWeaponMenu + 9) % 10;
			lastNavTime = gameLocal.time;
		}
		if (canNavigate && ac_NavDownWeaponMenu) {
			ac_cursorWeaponMenu = (ac_cursorWeaponMenu + 1) % 10;
			lastNavTime = gameLocal.time;
		}
	}
}

/*
================
rvVehicleWalker::ACUpdateWeaponMenu
  Each frame the function checks the current state of the weapo menu to the GUI itself. The GUI reads these state variables to display the weapon menu screen using pre-existing main menu assets.
================
*/
void rvVehicleWalker::ACUpdateWeaponMenu(void) {
	idUserInterface* hud = GetHud();
	if (!hud) {
		return;
	}

	hud->SetStateFloat("ac_assault_energy",
		ac_maxAssaultBoost > 0.0f ? ac_energyAssaultBoost / ac_maxAssaultBoost : 0.0f);
	hud->SetStateFloat("ac_flight_energy",
		ac_maxFlight > 0.0f ? ac_energyFlight / ac_maxFlight : 0.0f);

	hud->SetStateInt("ac_weaponmenu_open", ac_openWeaponMenu ? 1 : 0);

	{
		const char* armLName = "---";
		const char* armRName = "---";
		const char* shoulderLName = "---";
		const char* shoulderRName = "---";
		for (int j = 0; j < 10; j++) {
			if (idStr::Icmp(ACWEAPONSDEFS[j], ac_slotsWeaponMenu[0]) == 0) { armLName = ACWEAPONSNAMES[j]; }
			if (idStr::Icmp(ACWEAPONSDEFS[j], ac_slotsWeaponMenu[1]) == 0) { armRName = ACWEAPONSNAMES[j]; }
			if (idStr::Icmp(ACWEAPONSDEFS[j], ac_slotsWeaponMenu[2]) == 0) { shoulderLName = ACWEAPONSNAMES[j]; }
			if (idStr::Icmp(ACWEAPONSDEFS[j], ac_slotsWeaponMenu[3]) == 0) { shoulderRName = ACWEAPONSNAMES[j]; }
		}
		hud->SetStateString("ac_arm_display1", va("ARM L:%s", armLName));
		hud->SetStateString("ac_arm_display2", va("ARM R:%s", armRName));
		hud->SetStateString("ac_shoulder_display1", va("SHOULDER L:%s", shoulderLName));
		hud->SetStateString("ac_shoulder_display2", va("SHOULDER R:%s", shoulderRName));
	}

	{
		static const char* slotLabels[4] = { "ARM LEFT ", "ARM RIGHT", "SHOULDER LEFT", "SHOULDER RIGHT" };
		for (int i = 0; i < 4; i++) {
			const char* cursor;

			if (i == ac_slotcursorWeaponMenu) {
				cursor = ac_slotselectedWeaponMenu ? ">>" : "> ";
			}
			else {
				cursor = " ";
			}
			
			const char* wpnName = "---";
			for (int j = 0; j < 10; j++) {
				if (idStr::Icmp(ACWEAPONSDEFS[j], ac_slotsWeaponMenu[i]) == 0) {
					wpnName = ACWEAPONSNAMES[j];
					break;
				}
			}
			hud->SetStateString(va("weaponmenu_slot%d_row", i),
				va("%s%s:  %s", cursor, slotLabels[i], wpnName));
		}
	}

	for (int i = 0; i < 10; i++) {
		const char* cursor = (ac_slotselectedWeaponMenu && i == ac_cursorWeaponMenu) ? "> " : " ";
		hud->SetStateString(va("weaponmenu_weapon%d_row", i),
			va("[%s%s", cursor, ACWEAPONSNAMES[i]));
	}
}

/*
================
rvVehicleWalker::ACQuickBoostManage
  Quick Boost: A rapid dash to the left/right like in AC6.
================
*/
void rvVehicleWalker::ACQuickBoostManage(void) {
	float deltaTime = MS2SEC(gameLocal.GetMSec());

	if (ac_activeQuickBoost) {
		int elapsed = gameLocal.time - ac_startQuickBoost;
		if (elapsed >= ac_durationQuickBoost) {
			
			ac_activeQuickBoost = false;
			ac_cooldownendQuickBoost = gameLocal.time + ac_cooldownQuickBoost;
			return;
		}

		float progress = (float)elapsed / (float)ac_durationQuickBoost;
		float strength = 1.0f - (progress * progress);
		additionalDelta += ac_directionQuickBoost * ac_speedQuickBoost * deltaTime * strength;
		return;
	}

	if (!ac_holdShift) {
		return;
	}
	if (gameLocal.time < ac_cooldownendQuickBoost) {
		return;
	}
	if (ac_activeAssaultBoost) {
		return;
	}

	usercmd_t& cmd = positions[0].mInputCmd;
	idVec3 boostDir(0, 0, 0);

	bool hasLateral = (cmd.rightmove != 0);
	bool hasBackward = (cmd.forwardmove < 0);
	if (!hasLateral && !hasBackward) {
		return;
	}

	if (cmd.forwardmove > 0) {
		boostDir.x = 1.0f;
	}
	else if (cmd.forwardmove < 0) {
		boostDir.x = -1.0f;
	}
	
	if (cmd.rightmove < 0) {
		boostDir.z = -1.0f;
	}
	else if (cmd.rightmove > 0) {
		boostDir.z = 1.0f;
	}

	boostDir.Normalize();

	ac_activeQuickBoost = true;
	ac_startQuickBoost = gameLocal.time;
	ac_directionQuickBoost = boostDir;
}

/*
================
rvVehicleWalker::ACAssaultBoostManage
  Assault Boost: A sustained high speed forward charge like in AC6. When in use, it drains energy while active and regenerates when not in a boosting state.It cannot activate during Quick Boost.
================
*/
void rvVehicleWalker::ACAssaultBoostManage(void) {
	float deltaTime = MS2SEC(gameLocal.GetMSec());

	if (!ac_activeAssaultBoost) {
		if (ac_energyAssaultBoost < ac_maxAssaultBoost) {
			ac_energyAssaultBoost += ac_regenAssaultBoost * deltaTime;
			if (ac_energyAssaultBoost > ac_maxAssaultBoost) {
				ac_energyAssaultBoost = ac_maxAssaultBoost;
			}
		}
	}

	bool shouldBoost = ac_holdShift && vfl.forward && !ac_activeQuickBoost && ac_energyAssaultBoost > 0.0f;

	if (shouldBoost) {
		ac_activeAssaultBoost = true;
		if (ac_startAssaultBoost == 0) {
			ac_startAssaultBoost = gameLocal.time;
		}

		ac_energyAssaultBoost -= ac_drainAssaultBoost * deltaTime;
		if (ac_energyAssaultBoost < 0.0f) {
			ac_energyAssaultBoost = 0.0f;
		}

		additionalDelta.x += ac_speedAssaultBoost * deltaTime;
	}
	else {
		ac_activeAssaultBoost = false;
		ac_startAssaultBoost = 0;
	}
}

/*
================
rvVehicleWalker::ACFlightManage
  Vertical Flight: Continuous vertical thrust up/down like in AC6.
  Makes use of the SetLinearVelocity function on physics object in order to have a more seamless flight movement. Contains its own energy system, which drains while thrusting and then regenerates when is on the ground.
================
*/
void rvVehicleWalker::ACFlightManage(void) {
	float deltaTime = MS2SEC(gameLocal.GetMSec());
	bool onGround = physicsObj.OnGround();

	if (onGround) {
		ac_timeFlight = gameLocal.time;
	}

	if (onGround && !ac_holdFlyUp && !ac_holdFlyDown) {
		ac_Flying = false;
		if (ac_energyFlight < ac_maxFlight) {
			ac_energyFlight += ac_regenFlight * deltaTime;
			if (ac_energyFlight > ac_maxFlight) {
				ac_energyFlight = ac_maxFlight;
			}
		}
	}

	idVec3 currentVel = physicsObj.GetLinearVelocity();
	idVec3 upDir = -physicsObj.GetGravityNormal(); 
	bool   didThrust = false;

	if (ac_holdFlyUp && ac_energyFlight > 0.0f) {
		ac_Flying = true;

		ac_energyFlight -= ac_drainFlight * deltaTime;
		if (ac_energyFlight < 0.0f) {
			ac_energyFlight = 0.0f;
		}

		float maxUpSpeed = ac_thrustFlight * 0.5f;
		float currentUp = currentVel * upDir;

		if (currentUp < maxUpSpeed) {
			float thrustAmount = ac_thrustFlight * deltaTime;
			if (!ac_prevholdFlyUp) {
				thrustAmount *= 2.5f;
			}
			currentVel += upDir * thrustAmount;
		}
		didThrust = true;
	}

	if (ac_holdFlyDown && ac_energyFlight > 0.0f) {
		ac_Flying = true;

		ac_energyFlight -= ac_drainFlight * deltaTime;
		if (ac_energyFlight < 0.0f) {
			ac_energyFlight = 0.0f;
		}

		float maxDownSpeed = ac_thrustFlight * 0.5f;
		float currentDown = -(currentVel * upDir); 

		if (currentDown < maxDownSpeed) {
			float thrustAmount = ac_thrustFlight * deltaTime;
			if (!ac_prevholdFlyDown) {
				thrustAmount *= 2.5f;
			}
			currentVel -= upDir * thrustAmount;
		}
		didThrust = true;
	}

	if (didThrust) {
		physicsObj.SetLinearVelocity(currentVel);
		physicsObj.Activate();
	}
	else if (!onGround && ac_energyFlight <= 0.0f) {
		ac_Flying = false;
	}
}

/*
================
rvVehicleWalker::ACQuickTurnManage
  Quick Turn: Fast 180-degree snap turns like in AC6.
================
*/
void rvVehicleWalker::ACQuickTurnManage(void) {
	
	if (ac_activeQuickTurn) {
		int elapsed = gameLocal.time - ac_startQuickTurn;
		if (elapsed >= ac_durationQuickTurn) {
			viewAngles.yaw = ac_targetQuickTurn;
			viewAngles.Normalize360();
			ac_activeQuickTurn = false;
			ac_cooldownQuickTurn = gameLocal.time + 300;
			return;
		}

		float progress = (float)elapsed / (float)ac_durationQuickTurn;
		float smoothProgress = (1.0f - idMath::Cos(progress * idMath::PI)) * 0.5f;
		float yawDiff = idMath::AngleNormalize180(ac_targetQuickTurn - ac_yawQuickTurn);
		viewAngles.yaw = ac_yawQuickTurn + yawDiff * smoothProgress;
		viewAngles.Normalize360();

		idMat3 newAxis = viewAngles.ToMat3() * physicsObj.GetGravityAxis();
		physicsObj.SetAxis(newAxis);
		viewAxis = newAxis;

		return;
	}
	if (gameLocal.time < ac_cooldownQuickTurn) {
		return;
	}
	if (ac_activeQuickBoost) {
		return;
	}
	if (ac_openWeaponMenu) {
		return;
	}

	bool leftJustPressed = (ac_holdTurnLeft && !ac_prevholdTurnLeft);
	bool rightJustPressed = (ac_holdTurnRight && !ac_prevholdTurnRight);

	if (!leftJustPressed && !rightJustPressed) {
		return;
	}

	ac_activeQuickTurn = true;
	ac_startQuickTurn = gameLocal.time;
	ac_yawQuickTurn = viewAngles.yaw;

	if (leftJustPressed) {
		ac_targetQuickTurn = viewAngles.yaw + 180.0f;  // sweeps to the left
	}
	else {
		ac_targetQuickTurn = viewAngles.yaw - 180.0f;  // sweeps to the right
	}
}

/*
================
rvVehicleWalker::ACFasterMovement
  Implements a faster speed value onto the walker's default movement speed. the base speed multiplier to overall movement. It scales with the additionalDelta that gets added onto, in the parent Think() function, which makes all of the movement faster in return.
================
*/
void rvVehicleWalker::ACFasterMovement(void) {
	
	if (ac_fasterMovement <= 1.0f) {
		return;
	}

	idVec3 animDelta;
	animator.GetDelta(gameLocal.time - gameLocal.GetMSec(), gameLocal.time, animDelta);

	float extraScale = ac_fasterMovement - 1.0f;
	additionalDelta += animDelta * extraScale;
}

// mekberg: overloaded this because physics bounds code is significantly different
/*
=====================
rvVehicleWalker::FindClearExitPoint
=====================
*/
// FIXME: this whole function could be cleaned up
bool rvVehicleWalker::FindClearExitPoint( int pos, idVec3& origin, idMat3& axis ) const {
	trace_t		trace;
	const rvVehiclePosition*	position = GetPosition( pos );
	idActor*	driver = position->GetDriver();
	idVec3		end;
	idVec3		traceOffsetPoints[4];
	const float error = 1.1f;

	origin.Zero();
	axis.Identity();

	idMat3 driverAxis = driver->viewAxis;
	idVec3 driverOrigin = driver->GetPhysics()->GetOrigin();

	idMat3 vehicleAxis = position->GetEyeAxis();
	idVec3 vehicleOrigin = GetPhysics()->GetOrigin();

	idBounds driverBounds( driver->GetPhysics()->GetBounds() );
	idBounds vehicleBounds( GetPhysics()->GetBounds() );
	idBounds driverAbsBounds;
	idBounds vehicleAbsBounds;

	vehicleAbsBounds.FromTransformedBounds( vehicleBounds, vehicleOrigin, GetPhysics()->GetAxis() );
	if( position->fl.driverVisible ) {
		// May want to do this even if the driver isn't visible
		if( position->mExitPosOffset.LengthSqr() > VECTOR_EPSILON ) {
			axis = GetPhysics()->GetAxis() * position->mExitAxisOffset;
			origin = vehicleOrigin + position->mExitPosOffset * axis;
		} else {
			origin = driverOrigin;
			axis = (driver->IsBoundTo(this)) ? vehicleAxis : driverAxis;
		}
		return true;
	}

	// Build list
	// FIXME: try and find a cleaner way to do this
	traceOffsetPoints[ 0 ] = vehicleBounds.FindVectorToEdge( vehicleAxis[ 1 ] ) - driverBounds.FindVectorToEdge( -vehicleAxis[ 1 ] );
	traceOffsetPoints[ 1 ] = vehicleBounds.FindVectorToEdge( -vehicleAxis[ 1 ] ) - driverBounds.FindVectorToEdge( vehicleAxis[ 1 ] );
	traceOffsetPoints[ 2 ] = vehicleBounds.FindVectorToEdge( vehicleAxis[ 0 ] ) - driverBounds.FindVectorToEdge( -vehicleAxis[ 0 ] );
	traceOffsetPoints[ 3 ] = vehicleBounds.FindVectorToEdge( -vehicleAxis[ 0 ] ) - driverBounds.FindVectorToEdge( vehicleAxis[ 0 ] );

	for( int ix = 0; ix < 4; ++ix ) {
		//Try all four sides and on top if need be
		end = vehicleOrigin + traceOffsetPoints[ ix ] * error;
// RAVEN BEGIN
// ddynerman: multiple clip worlds
		gameLocal.Translation( this, trace, vehicleOrigin, end, driver->GetPhysics()->GetClipModel(), driverAxis, driver->GetPhysics()->GetClipMask(), this, driver );
// RAVEN END
		driverAbsBounds.FromTransformedBounds( driverBounds, trace.endpos, driverAxis );
		if( trace.fraction > 0.0f && !driverAbsBounds.IntersectsBounds(vehicleAbsBounds) ) {
			origin = trace.endpos;
			axis = vehicleAxis;
			return true;
		}
	}

	return false;
}

/*
===============================================================================

	States 

===============================================================================
*/

CLASS_STATES_DECLARATION ( rvVehicleWalker )
	STATE ( "ForwardLeft",			rvVehicleWalker::Frame_ForwardLeft )
	STATE ( "ForwardRight",			rvVehicleWalker::Frame_ForwardRight )
	STATE ( "BackwardLeft",			rvVehicleWalker::Frame_BackwardLeft )
	STATE ( "BackwardRight",		rvVehicleWalker::Frame_BackwardRight )

	STATE ( "Wait_OnlineAnim",		rvVehicleWalker::State_Wait_OnlineAnim )
	
	STATE ( "State_Idle",			rvVehicleWalker::State_Idle )
	STATE ( "State_IdleThink",		rvVehicleWalker::State_IdleThink )
	STATE ( "State_IdleOffline",	rvVehicleWalker::State_IdleOffline )
	STATE ( "State_Offline",		rvVehicleWalker::State_Offline )
	STATE ( "State_Online",			rvVehicleWalker::State_Online )

	STATE ( "State_ForwardStart",	rvVehicleWalker::State_ForwardStart )
	STATE ( "State_Forward",		rvVehicleWalker::State_Forward )
	STATE ( "State_BackwardStart",	rvVehicleWalker::State_BackwardStart )
	STATE ( "State_Backward",		rvVehicleWalker::State_Backward )
	STATE ( "State_Stop",			rvVehicleWalker::State_Stop )
	STATE ( "State_Turn",			rvVehicleWalker::State_Turn )	
	STATE ( "State_TurnThink",		rvVehicleWalker::State_TurnThink )
	STATE ( "State_ScriptedAnim",	rvVehicleWalker::State_ScriptedAnim )
END_CLASS_STATES

/*
================
rvVehicleWalker::State_IdleOffline
================
*/
stateResult_t rvVehicleWalker::State_IdleOffline ( const stateParms_t& parms ) {
	vfl.frozen = true;

	PlayCycle ( ANIMCHANNEL_LEGS, "idle_offline", parms.blendFrames );
	PostAnimState ( ANIMCHANNEL_LEGS, "Wait_Driver", 2 );
	PostAnimState ( ANIMCHANNEL_LEGS, "State_Online", 2 );
	
	return SRESULT_DONE;
}

/*
================
rvVehicleWalker::State_Online
================
*/
stateResult_t rvVehicleWalker::State_Online ( const stateParms_t& parms ) {	
	vfl.frozen = false;
	
	PlayAnim ( ANIMCHANNEL_LEGS, "start", parms.blendFrames );
	PostAnimState ( ANIMCHANNEL_LEGS, "Wait_OnlineAnim", 4 );
	PostAnimState ( ANIMCHANNEL_LEGS, "State_Idle", 4 );

	return SRESULT_DONE;
}

/*
================
rvVehicleWalker::State_Offline
================
*/
stateResult_t rvVehicleWalker::State_Offline ( const stateParms_t& parms ) {	
	PlayAnim ( ANIMCHANNEL_LEGS, "stop", parms.blendFrames );
	PostAnimState ( ANIMCHANNEL_LEGS, "Wait_TorsoAnim", 4 );
	PostAnimState ( ANIMCHANNEL_LEGS, "State_IdleOffline", 4 );
	return SRESULT_DONE;
}

/*
================
rvVehicleWalker::State_Idle
================
*/
stateResult_t rvVehicleWalker::State_Idle ( const stateParms_t& parms ) {	
	if ( SRESULT_WAIT != State_IdleThink ( parms ) ) {
		return SRESULT_DONE;
	}
	
	PlayCycle( ANIMCHANNEL_LEGS, "idle", parms.blendFrames );
	PostAnimState ( ANIMCHANNEL_LEGS, "State_IdleThink", 2 );
	
	return SRESULT_DONE;
}

/*
================
rvVehicleWalker::State_Idle
================
*/
stateResult_t rvVehicleWalker::State_IdleThink ( const stateParms_t& parms ) { 
	if ( !vfl.driver || vfl.stalled ) {
		PostAnimState ( ANIMCHANNEL_LEGS, "State_Offline", parms.blendFrames );
		return SRESULT_DONE;
	}

	if ( IsMovementEnabled ( ) ) {
		if ( vfl.forward ) {
			PostAnimState ( ANIMCHANNEL_LEGS, "State_ForwardStart", 2 );
			return SRESULT_DONE;
		}
		
		if ( vfl.backward ) {
			PostAnimState ( ANIMCHANNEL_LEGS, "State_BackwardStart", 2 );
			return SRESULT_DONE;
		}
		
		if ( vfl.right || vfl.left ) {
			PostAnimState ( ANIMCHANNEL_LEGS, "State_Turn", 2 );
			return SRESULT_DONE;
		}
	}
	
	return SRESULT_WAIT;
}

/*
================
rvVehicleWalker::State_ForwardStart
================
*/
stateResult_t rvVehicleWalker::State_ForwardStart ( const stateParms_t& parms ) {
	PlayAnim ( ANIMCHANNEL_LEGS, "forward_start", 2 );
	PostAnimState ( ANIMCHANNEL_LEGS, "Wait_TorsoAnim", 2 );
	PostAnimState ( ANIMCHANNEL_LEGS, "State_Forward", 2 );
	return SRESULT_DONE;
}

stateResult_t rvVehicleWalker::State_Forward ( const stateParms_t& parms ) {
	// If not moving anymore by the time we get here just play the stop anim
	if ( !vfl.forward ) {
		stopAnimName = "forward_stop_leftmid";
		SetAnimState ( ANIMCHANNEL_LEGS, "State_Stop", 4 );
		return SRESULT_DONE;
	}

	if ( !parms.stage ) {
		PlayCycle( ANIMCHANNEL_LEGS, "forward", 2 );
		return SRESULT_STAGE(parms.stage + 1);
	}

	if ( AnimDone( ANIMCHANNEL_LEGS, 2 ) ) {
		return SRESULT_DONE;
	}

	HandleStrafing();
	return SRESULT_WAIT;
}

/*
================
rvVehicleWalker::State_BackwardStart
================
*/
stateResult_t rvVehicleWalker::State_BackwardStart ( const stateParms_t& parms ) {
	PlayAnim ( ANIMCHANNEL_LEGS, "backward_start", parms.blendFrames );
	PostAnimState ( ANIMCHANNEL_LEGS, "Wait_TorsoAnim", 2 );
	PostAnimState ( ANIMCHANNEL_LEGS, "State_Backward", 2 );
	return SRESULT_DONE;
}

stateResult_t rvVehicleWalker::State_Backward ( const stateParms_t& parms ) {
	// If not moving anymore by the time we get here just play the stop anim
	if ( !vfl.backward ) {
		stopAnimName = "backward_stop_leftmid";
		SetAnimState ( ANIMCHANNEL_LEGS, "State_Stop", 2 );
		return SRESULT_DONE;
	}
		
	if ( !parms.stage ) {
	PlayCycle( ANIMCHANNEL_LEGS, "backward", 2 );
		return SRESULT_STAGE(parms.stage + 1);
	}

	if ( AnimDone( ANIMCHANNEL_LEGS, 2 ) ) {
		return SRESULT_DONE;
	}

	HandleStrafing();
	return SRESULT_WAIT;
}

/*
================
rvVehicleWalker::State_Stop
================
*/
stateResult_t rvVehicleWalker::State_Stop ( const stateParms_t& parms ) {	
	PlayAnim ( ANIMCHANNEL_LEGS, stopAnimName, parms.blendFrames );
	PostAnimState ( ANIMCHANNEL_LEGS, "Wait_TorsoAnim", 2 );
	PostAnimState ( ANIMCHANNEL_LEGS, "State_Idle", 2 );
	return SRESULT_DONE;
}

/*
================
rvVehicleWalker::State_Turn
================
*/
stateResult_t rvVehicleWalker::State_Turn ( const stateParms_t& parms ) {
	if ( vfl.left ) {
		PlayAnim ( ANIMCHANNEL_LEGS, "turn_left", parms.blendFrames );
	} else if ( vfl.right ) {
		PlayAnim ( ANIMCHANNEL_LEGS, "turn_right", parms.blendFrames );
	} else {
		PostAnimState ( ANIMCHANNEL_LEGS, "State_Idle", parms.blendFrames );
		return SRESULT_DONE;
	}
	
	PostAnimState ( ANIMCHANNEL_LEGS, "State_TurnThink", 16 );
	
	return SRESULT_DONE;
}

/*
================
rvVehicleWalker::State_TurnThink
================
*/
stateResult_t rvVehicleWalker::State_TurnThink ( const stateParms_t& parms ) {
	// If moving again bail on the turn, reguardless of whether its in mid animation
	if ( vfl.forward || vfl.backward ) {
		PostAnimState ( ANIMCHANNEL_LEGS, "State_Idle", parms.blendFrames );		
		return SRESULT_DONE;
	}
	// If the animation is done then repeat
	if ( AnimDone ( ANIMCHANNEL_LEGS, 8 ) ){
		PostAnimState ( ANIMCHANNEL_LEGS, "State_Turn", 8 );
		return SRESULT_DONE;
	}

	HandleStrafing();

	return SRESULT_WAIT;
}

/*
================
rvVehicleWalker::Frame_ForwardLeft
================
*/
stateResult_t rvVehicleWalker::Frame_ForwardLeft ( int ) {
	if ( !vfl.forward ) {
		stopAnimName = "forward_stop_left";
		SetAnimState ( ANIMCHANNEL_LEGS, "State_Stop", 2 );
	}
	return SRESULT_OK;
}

/*
================
rvVehicleWalker::Frame_ForwardRight
================
*/
stateResult_t rvVehicleWalker::Frame_ForwardRight ( int ) {
	if ( !vfl.forward ) {
		stopAnimName = "forward_stop_right";
		SetAnimState ( ANIMCHANNEL_LEGS, "State_Stop", 2 );
	}
	return SRESULT_OK;
}


/*
================
rvVehicleWalker::Frame_BackwardLeft
================
*/
stateResult_t rvVehicleWalker::Frame_BackwardLeft ( int ) {
	if ( !vfl.backward ) {
		stopAnimName = "backward_stop_left";
		SetAnimState ( ANIMCHANNEL_LEGS, "State_Stop", 2 );
	}
	return SRESULT_OK;
}

/*
================
rvVehicleWalker::Frame_BackwardRight
================
*/
stateResult_t rvVehicleWalker::Frame_BackwardRight ( int ) {
	if ( !vfl.backward ) {
		stopAnimName = "backward_stop_right";
		SetAnimState ( ANIMCHANNEL_LEGS, "State_Stop", 2 );
	}
	return SRESULT_OK;
}

/*
================
rvVehicleWalker::State_Wait_OnlineAnim
================
*/
stateResult_t rvVehicleWalker::State_Wait_OnlineAnim ( const stateParms_t& parms ) {	
	if ( !AnimDone ( ANIMCHANNEL_LEGS, parms.blendFrames ) && vfl.driver ) {
		return SRESULT_WAIT;
	}
	return SRESULT_DONE;
}	

/*
================
rvVehicleWalker::State_ScriptedAnim
================
*/
stateResult_t rvVehicleWalker::State_ScriptedAnim ( const stateParms_t& parms ) {
	if ( !AnimDone ( ANIMCHANNEL_LEGS, parms.blendFrames ) ) {
		return SRESULT_WAIT;
	}
	Event_ScriptedStop();
	return SRESULT_DONE;
}

/*
================
rvVehicleWalker::Event_ScriptedAnim
================
*/
void rvVehicleWalker::Event_ScriptedAnim( const char* animname, int blendFrames, bool loop, bool endWithIdle ) {
	vfl.endWithIdle = endWithIdle;
	if ( loop ) {
		PlayCycle ( ANIMCHANNEL_LEGS, animname, blendFrames );
	} else {
		PlayAnim ( ANIMCHANNEL_LEGS, animname, blendFrames );
	}
	SetAnimState ( ANIMCHANNEL_LEGS, "State_ScriptedAnim", blendFrames );
	vfl.scripted = true;
}

/*
================
rvVehicleWalker::Event_ScriptedDone
================
*/
void rvVehicleWalker::Event_ScriptedDone( void ) {
	idThread::ReturnInt( !vfl.scripted );
}

/*
================
rvVehicleWalker::Event_ScriptedStop
================
*/
void rvVehicleWalker::Event_ScriptedStop( void ) {
	vfl.scripted = false;

	if ( vfl.endWithIdle ) {
		SetAnimState ( ANIMCHANNEL_LEGS, "State_Idle", 2 );
	}
}
