globals [ 
  cstep ;confirmed
  time  ;confirmed
  timing? ;confirmed
  BlueScore ;TBD
  RedScore ;TBD
  running? ;confirmed 
  BlueLoads
  RedLoads 
  robotsketch_array
  robot_array
  fireCheck
  frames_array
  currFrame
  lastTimeFramed
  pyramids_array
  TURN_SCALE
  DRIVE_SCALE
  ]
breed [tiles tile]
breed [tape tapesing]
breed [balls ball]
breed [robots robot]
breed [rollers roller]
breed [primary-launchers primary-launcher]
breed [secondary-launchers secondary-launcher]
breed [baseDrives baseDrive]
breed [robotSketches robotSketch]
breed [frames frame]

frames-own [
  frameID
  currentrobot_array
  robotXs
  robotYs
  robotHs
  robotCaps
  robotEls
  pyramids
  bScore
  rScore
  bLoads
  rLoads
]

balls-own [
  pyramidID
  targetX
  targetY
  alliance
  status
]

robotSketches-own [
  ID
  fdbkdrive_speed
  sidedrive_speed
  intake_sides
  primary_launcher_sides
  primary_launcher_speed
  secondary_launcher_sides
  secondary_launcher_speed
  lift_type
]

robots-own [
  robotID
  robotSketchID
  startingTile
  alliance
  elevation
  capacity
]

rollers-own [
  rollerID
]

primary-launchers-own [
  plaunchID
]

secondary-launchers-own [
  slaunchID
]

basedrives-own [
  baseID
]

to startup
  hardreset
end

to reset-field
  clear-drawing
  ask robots [
    set capacity []
    set elevation "None"
  ]
  set lasttimeframed -5
  set currFrame 0
  set frames_array []
  set pyramids_array []
  set timing? false
  set running? false
  set BlueLoads 32
  set RedLoads 32
  set cstep -1
  set time 0
  set fireCheck 0
  set BlueScore 0
  set RedScore 0
  set TURN_SCALE 0.05
  set DRIVE_SCALE 1
  clear-output
  ask balls with [shape = "nbnpyramid"]
  [
    set size 10
    set status "Standing"
    if not (xcor < 5 or xcor > 25 or ycor < 4 or ycor > 26)
    [
      set heading random 360
    ]
  ]
  resetbots
  reset-frames
end

to hardreset
  ca
  reset-ticks
  reset-field
  set robotsketch_array []
  set robot_array []
  set frames_array []
  ask patches [
    set pcolor grey
  ]
  create-tiles 1 [
    set shape "tile"
    set color blue
    set size 50
    setxy 2 7
  ]
  create-tiles 1 [
    set shape "tile"
    set color blue
    set size 50
    setxy 7 2
  ]
  create-tiles 1 [
    set shape "tile"
    set color red
    set size 50
    setxy 22 2
  ]
  create-tiles 1 [
    set shape "tile"
    set color red
    set size 50
    setxy 27 7
  ]
  create-tiles 1 [
    set shape "tri"
    set color blue
    set size 50
    setxy 27 27
    set heading 180
  ]
  create-tiles 1 [
    set shape "tri"
    set color red
    set size 50
    setxy 2 27
    set heading 90
  ]
  create-tape 1 [
    set shape "circle"
    set size 0.5
    set color white
    setxy 0 9.25
    hatch 1
    set heading towardsxy 9.25 0
    while[xcor < 9.25]
    [
      fd 0.05
      hatch 1
    ]
    set heading 0
    while[ycor < 9.25]
    [
      fd 0.05
      hatch 1
    ]
    set heading 270
    while[xcor > 0]
    [
      fd 0.05
      hatch 1
    ]
  ]
  create-tape 1 [
    set shape "circle"
    set size 0.5
    set color white
    setxy 29 9.25
    hatch 1
    set heading towardsxy 19.75 0
    while[xcor > 19.75]
    [
      fd 0.01
      hatch 1
    ]
    set heading 0
    while[ycor < 9.25]
    [
      fd 0.01
      hatch 1
    ]
    set heading 90
    while[xcor < 29]
    [
      fd 0.01
      hatch 1
    ]
  ]
  create-tape 1 [
    set shape "circle"
    set size 0.5
    set color white
    setxy 9.25 9.25
    hatch 1
    set heading towardsxy 24.75 24.75
    while[xcor < 24.75]
    [
      fd 0.01
      hatch 1
    ]
  ]
  create-tape 1 [
    set shape "circle"
    set size 0.5
    set color white
    setxy 19.75 9.25
    hatch 1
    set heading towardsxy 4.25 24.75
    while[xcor > 4.25]
    [
      fd 0.01
      hatch 1
    ]
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 19.75 9.25
    set pyramidID "Pyr0"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 9.25 9.25
    set pyramidID "Pyr1"
    ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 9.25 19.75
    set pyramidID "Pyr2"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 19.75 19.75
    set pyramidID "Pyr3"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 14.5 0.5
    set heading 180
    set pyramidID "Pyr4"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 14.5 5
    set pyramidID "Pyr5"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 14.5 24
    set pyramidID "Pyr6"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 14.5 28.5
    set heading 0
    set pyramidID "Pyr7"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 0.5 14.5
    set heading 270
    set pyramidID "Pyr8"
  ]
  create-balls 1 [
    set shape "nbnpyramid"
    set size 10
    setxy 28.5 14.5
    set heading 90
    set pyramidID "Pyr9"
  ]
end

to up
  if running?
  [
    ask robots with [startingtile = robotbeingdriven and elevation = "None"] [
      let checkID robotsketchID
      set xcor (xcor + (sin(heading) * 0.5 * first([fdbkdrive_speed] of robotsketches with [ID = checkID]))) 
      set ycor (ycor + (cos(heading) * 0.5 * first([fdbkdrive_speed] of robotsketches with [ID = checkID])))    
    ]
    rebuildbots
  ]
end

to down
  if running?
  [
    ask robots with [startingtile = robotbeingdriven and elevation = "None"] [
      let checkID robotsketchID
      set xcor (xcor - (sin(heading) * 0.5 * first([fdbkdrive_speed] of robotsketches with [ID = checkID]))) 
      set ycor (ycor - (cos(heading) * 0.5 * first([fdbkdrive_speed] of robotsketches with [ID = checkID])))
    ]
    rebuildbots
  ]
end

to rturn
  if running?
  [
    ask robots with [startingtile = robotbeingdriven and elevation = "None"]  [
      let checkID robotsketchID
    set heading (heading + 10 * first([fdbkdrive_speed] of robotsketches with [ID = checkID]))
    ]
    rebuildbots
  ]
end

to lturn
  if running?
  [
    ask robots with [startingtile = robotbeingdriven and elevation = "None"]  [
      let checkID robotsketchID
      set heading (heading - 10 * first([fdbkdrive_speed] of robotsketches with [ID = checkID]))
    ]
    rebuildbots
  ]
end

to strafeR
  if running?
  [
    ask robots with [startingtile = robotbeingdriven and elevation = "None"]  [
      let checkID robotsketchID
      set xcor (xcor + (sin(heading + 90) * 0.5 * first([sidedrive_speed] of robotsketches with [ID = checkID]))) 
      set ycor (ycor + (cos(heading + 90) * 0.5 * first([sidedrive_speed] of robotsketches with [ID = checkID])))
    ]
    rebuildbots
  ]
end

to strafeL
  if running?
  [
    ask robots with [startingtile = robotbeingdriven and elevation = "None"]  [
      let checkID robotsketchID
      set xcor (xcor - (sin(heading + 90) * 0.5 * first([sidedrive_speed] of robotsketches with [ID = checkID]))) 
      set ycor (ycor - (cos(heading + 90) * 0.5 * first([sidedrive_speed] of robotsketches with [ID = checkID])))
    ]
    rebuildbots
  ]
end

to shoot
  if running?
  [
    ask robots with [startingtile = robotbeingdriven and elevation = "None"] [
      let checkID robotsketchID
      let checkID2 robotID
      if(length capacity > 0)
      [
        set fireCheck checkID2
      ]
    ]
  ]
end

to crtbls
  if fireCheck != 0
  [
  create-balls 1 [
          set shape "nbnball"
          set color last first([capacity] of robots with [robotID = fireCheck])
          set size 7.5
          setxy first([xcor] of robots with [robotID = fireCheck]) first([ycor] of robots with [robotID = fireCheck])
          set heading first([heading] of robots with [robotID = fireCheck])
          set alliance first([alliance] of robots with [robotID = fireCheck]) 
          ifelse(alliance = "Blue")
          [
            set targetX 27.5
            set targetY 27.5
          ]
          [
            set targetX 1.5
            set targetY 27.5
          ]                 
        ]
  ask robots with [robotID = fireCheck]
  [
    set capacity remove-item (length capacity - 1) capacity
  ]
  set fireCheck 0
  ]
end

to go
  if running?
  [
    ask robots
    [
      if (xcor < 1)
      [
        set xcor 1
      ]
      if (ycor < 1)
      [
        set ycor 1
      ]
      if (xcor > 28)
      [
        set xcor 28
      ]
      if (ycor > 28)
      [
        set ycor 28
      ]
      
    ]
    crtbls
    rebuildbots
    ask balls with [shape = "nbnpyramid"][
      let closestRoller min-one-of rollers [distancexy [xcor] of myself [ycor] of myself]
      let checkID [rollerID] of closestRoller
      if(distance closestRoller < 1.25 and length first([capacity] of robots with [robotID = checkID]) = 0 and status = "Standing")
      [
        ask robots with [robotID = checkID]
        [
          set capacity [green green green orange]
        ]
        set size 0
        set status "Intaken"
      ]
    ]
    ask balls with [shape = "nbnball"] [
      ifelse(distancexy 27.5 27.5 > 0.5)
      [
        ifelse(distancexy 1.5 27.5 > 0.5)
        [
          fd 0.25
          if(xcor < 0.5)
          [
            die
          ]
          if(ycor < 0.5)
          [
            die
          ]
          if(xcor > 28.5)
          [
            die
          ]
          if(ycor > 28.5)
          [
            die
          ]
        ]
        [
          ifelse(color = orange)
          [
            set redscore redscore + 10
          ]
          [
            set redscore redscore + 5
          ]
          die
        ]
      ]
      [
        ifelse(color = orange)
        [
          set bluescore bluescore + 10
        ]
        [
          set bluescore bluescore + 5
        ]
        die
      ]
    ]
    ifelse not Practice?
    [
      commentary
    ]
    [
      if cstep < 4
      [
        output-print "Practice! No timer and unlimited frames creation,"
        output-print "but rules are still enforced"
      ]
      set time 90
      set cstep 4
    ]
    if timing?
    [
      set time timer
      if time >= lasttimeframed + 2
      [
        set lasttimeframed lasttimeframed + 2
        create-frames 1 [
          set size 0
          set frameID word "Frame" lasttimeframed
          set frames_array lput frameID frames_array
          let temprobotarray []
          let temprobotXarray []
          let temprobotYarray []
          let temprobotHarray []
          let temprobotCAParray []
          let temprobotELarray []
          let temppyramidsarray []
          let counter 0
          while [counter < length robot_array]
          [
            ask robots with [robotID = item counter robot_array] [
              set temprobotarray lput robotID temprobotarray
              set temprobotXarray lput xcor temprobotXarray
              set temprobotYarray lput ycor temprobotYarray
              set temprobotHarray lput heading temprobotHarray
              set temprobotCAParray lput capacity temprobotCAParray
              set temprobotELarray lput elevation temprobotELarray
            ]
            set counter counter + 1
          ]
          set counter 0
          while [counter < 10]
          [
            ask balls with [pyramidID = word "Pyr" counter] [
              set temppyramidsarray lput status temppyramidsarray
            ]
            set counter counter + 1
          ]
          set currentrobot_array temprobotarray
          set robotXs temprobotXarray
          set robotYs temprobotYarray
          set robotHs temprobotHarray
          set robotCAPs temprobotCAParray
          set robotELs temprobotElarray
          set pyramids temppyramidsarray
          set bscore blueScore
          set rscore redScore
          set bloads Blueloads
          set rloads redloads
        ]
      ]
    ]
    ask robots [
      pu
    ]
    wait 0.01
  ]
end

to commentary
  if(cstep = -1)
  [
    output-print "Preautonomous. Blue alliance, are you ready? (Press Thumbs Up!)"
    set cstep -0.5
  ]
  if(cstep = 0)
  [
    output-print "Autonomous begins in 3"
    wait 0.5
    output-print "2"
    wait 0.5
    output-print "1"
    wait 0.5
    output-print "Go!"
    set cstep 1
    set timing? true
    reset-timer
  ]
  if(timer >= 10 and cstep = 1)
  [
    output-print "5 seconds left!"
    set cstep 2
  ]
  if(timer >= 15 and cstep = 2)
  [
    ifelse(bluescore > redscore)
    [
      set bluescore bluescore + 10
    ]
    [
      if(redscore > bluescore)
      [
        set redscore redscore + 10
      ]
    ]
    ifelse(first([alliance] of robots with [startingtile = robotbeingdriven]) = "Blue")
    [
      output-print (word "Time's up! You scored " bluescore " !") 
    ]
    [
      output-print (word "Time's up! You scored " bluescore " !")       
    ]
    set cstep 3
    set timing? false
    set time 15
    set running? false
    wait 1
    output-print "Driver Control begins in 3"
    wait 0.5
    output-print "2"
    wait 0.5
    output-print "1"
    wait 0.5
    output-print "Go!"
    set timing? true
    set running? true
  ]
  if(timer >= 90 and cstep = 3)
  [
    output-print "30 seconds left!"
    set cstep 4
  ]
  if(timer >= 120 and cstep = 4)
  [
    
    set timing? false
    set time 120
    set running? false
    set cstep 5
    ask robots [
      ifelse elevation = "High" 
      [
        ifelse alliance = "Blue"
        [
          set bluescore bluescore + 50
        ]
        [
          set redscore redscore + 50
        ]
      ]
      [
        if elevation = "Low"
        [
          ifelse alliance = "Blue"
          [
            set bluescore bluescore + 25
          ]
          [
            set redscore redscore + 25
          ]
        ]
      ]
    ]
    ifelse(first([alliance] of robots with [startingtile = robotbeingdriven]) = "Blue")
    [
      output-print (word "Time's up! You scored " bluescore " !") 
    ]
    [
      output-print (word "Time's up! You scored " redscore " !")       
    ]
    ifelse bluescore > redscore
    [
      output-print "Blue Alliance wins!"
    ]
    [
      ifelse redscore > bluescore
      [
        output-print "Red Alliance wins!"
      ]
      [
        output-print "Tie!"
      ]
    ]
  ]
end

to load
  ask robots with [startingTile = robotbeingdriven]
  [
    if blueloads > 0
    [
    if elevation = "None" and length capacity < 4 [
      if(cstep < 0)
      [
        set capacity lput green capacity
        ifelse(alliance = "Blue")
        [
          set blueloads blueloads - 1
        ]
        [
          set redloads redloads - 1
        ]
      ]
      if(cstep > 2)
      [
        set capacity lput green capacity
        ifelse(alliance = "Blue")
        [
          set blueloads blueloads - 1
        ]
        [
          set redloads redloads - 1
        ]
      ]
    ]
    ]
    if redloads > 0
    [
      if elevation = "None" and length capacity < 4 [
      if(cstep < 0)
      [
        set capacity lput green capacity
        ifelse(alliance = "Blue")
        [
          set blueloads blueloads - 1
        ]
        [
          set redloads redloads - 1
        ]
      ]
      if(cstep > 2)
      [
        set capacity lput green capacity
        ifelse(alliance = "Blue")
        [
          set blueloads blueloads - 1
        ]
        [
          set redloads redloads - 1
        ]
      ]
    ]
    ]
  ]
end

to elevate
  ask robots with [startingTile = robotbeingdriven]
  [
    ifelse xcor <= 1.2 and ycor >= -0.12 and running? and time >= 90 and elevation = "None"
    [
      if (distance (max-one-of robots with [alliance = [alliance] of myself][distancexy xcor ycor]) < 1)
      [
        set elevation first([lift_type] of robotsketches with [ID = [robotID] of myself])
        ask robots with [alliance = [alliance] of myself and elevation = "None"]
        [
          set elevation "Being elevated"
        ]
      ]
    ]
    [
      if elevation != "Being elevated"
      [
        set elevation "None"
      ]
    ]
  ]
end

to importrobotsketch
  let newsketch_array read-from-string user-input "Please enter the exported sketch you would like to import:"
  set robotsketch_array lput first newsketch_array robotsketch_array
  create-robotsketches 1 [
    set ID item 0 newsketch_array
    set fdbkdrive_speed item 1 newsketch_array
    set sidedrive_speed item 2 newsketch_array
    set intake_sides item 3 newsketch_array
    set primary_launcher_sides item 4 newsketch_array
    set primary_launcher_speed item 5 newsketch_array
    set secondary_launcher_sides item 6 newsketch_array
    set secondary_launcher_speed item 7 newsketch_array
    set lift_type item 8 newsketch_array
    set size 0
  ]
end

to exportrobotsketch
  let sketchToExport user-one-of "Which sketch would you like to export?" robotsketch_array
  let exportArray (list
    first([ID] of robotsketches with [ID = sketchToExport]) 
    first([fdbkdrive_speed] of robotsketches with [ID = sketchToExport])
    first([sidedrive_speed] of robotsketches with [ID = sketchToExport])
    first([intake_sides] of robotsketches with [ID = sketchToExport])
    first([primary_launcher_sides] of robotsketches with [ID = sketchToExport])
    first([primary_launcher_speed] of robotsketches with [ID = sketchToExport])
    first([secondary_launcher_sides] of robotsketches with [ID = sketchToExport])
    first([secondary_launcher_speed] of robotsketches with [ID = sketchToExport])
    first([lift_type] of robotsketches with [ID = sketchToExport])
  )
  write exportArray
end

to deletesketch
  let sketch-to-be-deleted user-one-of "Which sketch would you like to delete?" robotsketch_array
  set robotsketch_array remove sketch-to-be-deleted robotsketch_array
  ask robotsketches with [ID = sketch-to-be-deleted]
  [
    die
  ]
end

to robotdelete
  let robot-to-be-deleted user-one-of "Which robot would you like to delete?" robot_array
  set robot_array remove robot-to-be-deleted robot_array
  ask robots with [robotID = robot-to-be-deleted]
  [
    die
  ]
  ask rollers with [rollerID = robot-to-be-deleted]
  [
    die
  ]
  ask primary-launchers with [plaunchID = robot-to-be-deleted]
  [
    die
  ]
  ask secondary-launchers with [slaunchID = robot-to-be-deleted]
  [
    die
  ]
  ask basedrives with [baseID = robot-to-be-deleted]
  [
    die
  ]
end

to robotsketchcreate
  let robot_name user-input "Please name the new sketch."
  while [ position robot_name robotsketch_array != false]
  [
    set robot_name user-input "Name already used. Please name the new sketch"
  ]
  set robotsketch_array lput robot_name robotsketch_array
  create-robotsketches 1 [
    set size 0
    set ID robot_name
  ]
  ask robotsketches with [ID = robot_name]
  [
    set fdbkdrive_speed read-from-string(user-input "What speed in fps can your robot move forwards and backwards? (Enter 0 if cannot move fd/bk)") / 2
    set sidedrive_speed read-from-string(user-input "What speed in fps can your robot move sideways? (Enter 0 if cannot move sideways)") / 2
    set intake_sides user-one-of "What side of the robot is your intake on?" ["Front" "Back" "Both"]
    set primary_launcher_sides user-one-of "How is your primary launcher oriented?" ["None" "Front" "Back"]
    set primary_launcher_speed read-from-string(user-input "How many bps from primary launcher? (Enter 0 if cannot shoot)")
    set secondary_launcher_sides user-one-of "How is your secondary launcher oriented?" ["None" "Front" "Back"]
    set secondary_launcher_speed read-from-string(user-input "How many bps from secondary launcher? (Enter 0 if cannot shoot)")
    set lift_type user-one-of "What lift type do you have?" ["None" "Low" "High"]
  ]
  user-message (word "Robot sketch " robot_name " created! (You still need to click Add Robot to add this robot to the field.)")
end

to resetbots
  ask robots [
    set heading 0
    ifelse(startingTile = "Far Blue")
    [
      setxy 2 7
      set alliance "Blue"
    ]
    [
      ifelse(startingTile = "Close Blue")
      [
        setxy 7 2
        set alliance "Blue"
      ]
      [
        ifelse(startingTile = "Far Red")
        [
          setxy 27 7
          set alliance "Red"
        ]
        [
          setxy 22 2
          set alliance "Red"
        ]
      ]
    ]
    set elevation "None"
  ]
  rebuildbots
end
to rebuildbots
  ask rollers [
    let checkID rollerID
    set heading first([heading] of robots with [robotID = checkID])
    set size 10
    setxy first([xcor] of robots with [robotID = checkID]) first([ycor] of robots with[robotID = checkID])
  ]
  ask baseDrives [
    let checkID baseID
    set heading first([heading] of robots with [robotID = checkID])
    set size 10
    setxy first([xcor] of robots with [robotID = checkID]) first([ycor] of robots with[robotID = checkID])
  ]
  ask primary-launchers [
    let checkID plaunchID
    set heading first([heading] of robots with [robotID = checkID])
    set size 10
    setxy first([xcor] of robots with [robotID = checkID]) first([ycor] of robots with[robotID = checkID])
  ]
  ask secondary-launchers [
    let checkID slaunchID
    set heading first([heading] of robots with [robotID = checkID])
    set size 10
    setxy first([xcor] of robots with [robotID = checkID]) first([ycor] of robots with[robotID = checkID])
  ]
end

to addrobottofield
  create-robots 1 [
    set shape "square"
    set heading 0
    set size 10
    let desiredrobotID user-input "Enter a name for this robot: (MUST be unique)"
    ask robots with [robotID = desiredrobotID] [die]
    set robot_array remove desiredrobotID robot_array
    set robotID desiredrobotID
    set robot_array lput robotID robot_array
    set robotsketchID user-one-of "Which sketch is this robot based off of?" robotsketch_array
    set startingTile user-one-of "Which starting tile?" ["Far Blue" "Close Blue" "Far Red" "Close Red"]
    set elevation "None"
    set capacity []
    ifelse(startingTile = "Far Blue")
    [
      setxy 2 7
      set alliance "Blue"
    ]
    [
      ifelse(startingTile = "Close Blue")
      [
        setxy 7 2
        set alliance "Blue"
      ]
      [
        ifelse(startingTile = "Far Red")
        [
          setxy 27 7
          set alliance "Red"
        ]
        [
          setxy 22 2
          set alliance "Red"
        ]
      ]
    ]
    set color (position robotID robot_array + 1) * 20 + 5

  ]
  create-rollers 1 [
    set rollerID last robot_array
    set shape (word "roller" first([intake_sides] of robotsketches with [ID = first ([robotSketchID] of robots with [robotID = last robot_array])]))
    set heading 0
    set size 10
    setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
  ]
  create-baseDrives 1 [
    set baseID last robot_array
    ifelse (first([fdbkdrive_speed] of robotsketches with [ID = first([robotSketchID] of robots with [robotID = last robot_array])]) = 0)
    [
      set shape "driveblank"
    ]
    [
      ifelse (first([sidedrive_speed] of robotsketches with [ID = first([robotSketchID] of robots with [robotID = last robot_array])]) = 0)
      [
        set shape "drivetank"
      ]
      [
        set shape "drivex"
      ]
    ]
    set heading 0
    set size 10
    setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
  ]
  create-primary-launchers 1 [
    set plaunchID last robot_array
    set shape (word "plaunch" first([primary_launcher_sides] of robotsketches with [ID = first ([robotSketchID] of robots with [robotID = last robot_array])]))
    set heading 0
    set size 10
    setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
  ]
  create-secondary-launchers 1 [
    set slaunchID last robot_array
    set shape (word "slaunch" first([secondary_launcher_sides] of robotsketches with [ID = first ([robotSketchID] of robots with [robotID = last robot_array])]))
    set heading 0
    set size 10
    setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
  ]
  user-message "Robot Added!"
end

to reset-frames
  set frames_array []
  ask frames [
    die
  ]
end

to add-frame
  create-frames 1 [
    set size 0
    set frameID user-input "Please name this frame: "
    let framesRand length frames_array
    let framesCheck false
    if frameID = ""
    [
      set framesCheck true
    ]
    while [not(position frameID frames_array = false and frameID != "")]
    [
      ifelse framesCHeck
      [
        set frameID word "Frame" framesRand
        set framesRand framesRand + 1
      ]
      [
        set frameID user-input "Invalid frame name. Please name this frame:"
      ]
    ]
    set frames_array lput frameID frames_array
    let temprobotarray []
    let temprobotXarray []
    let temprobotYarray []
    let temprobotHarray []
    let temprobotCAParray []
    let temprobotELarray []
    let temppyramidsarray []
    let counter 0
    while [counter < length robot_array]
    [
      ask robots with [robotID = item counter robot_array] [
        set temprobotarray lput robotID temprobotarray
        set temprobotXarray lput xcor temprobotXarray
        set temprobotYarray lput ycor temprobotYarray
        set temprobotHarray lput heading temprobotHarray
        set temprobotCAParray lput capacity temprobotCAParray
        set temprobotELarray lput elevation temprobotELarray
      ]
      set counter counter + 1
    ]
    set counter 0
    while [counter < 10]
    [
      ask balls with [pyramidID = word "Pyr" counter] [
        set temppyramidsarray lput status temppyramidsarray
      ]
      set counter counter + 1
    ]
    set currentrobot_array temprobotarray
    set robotXs temprobotXarray
    set robotYs temprobotYarray
    set robotHs temprobotHarray
    set robotCAPs temprobotCAParray
    set robotELs temprobotElarray
    set pyramids temppyramidsarray
    set bscore blueScore
    set rscore redScore
    set bloads Blueloads
    set rloads redloads
  ]
end

to dispFrame [frameBeingDisp]
  let actualFrame one-of frames with [frameID = frameBeingDisp]
  ask robots [
    pen-down
    set pen-size 10
    let indexInArray position robotID robot_array
    setxy item indexInArray [robotXs] of actualFrame item indexInArray [robotYs] of actualFrame
    set heading item indexinarray [robotHs] of actualFrame
    set capacity item indexinarray [robotcaps] of actualFrame
    set elevation item indexinarray [robotEls] of actualFrame
    pen-up    
  ]
  let counter 0
  while [counter < 10]
    [
      ask balls with [pyramidID = word "Pyr" counter] [
        ifelse (item counter ([pyramids] of actualFrame)) = "Standing"
        [
          set status "Standing"
          set size 10
        ]
        [
          set status "Intaken"
          set size 0
        ]
      ]
      set counter counter + 1
    ]
end

to showFrame
  let frameToBeDisp user-one-of "Please select a frame to display:" frames_array
  dispFrame frametobedisp
end

to deleteFrame
  let frameToBeDel user-one-of "Please select a frame to delete:" frames_array
  set frames_array remove frameToBeDel frames_array
  ask frames with [frameID = frameToBeDel]
  [
    die
  ]
end

to nextframe
  set currframe min list (currFrame + 1) (length frames_array - 1)
  dispFrame item currFrame frames_array
end

to previousframe
  set currframe max list (currFrame - 1) (0)
  dispFrame item currFrame frames_array
end

to exportFilm
  file-close-all
  file-open user-new-file
  file-print "--BEGIN FILE--"
  file-print "--ROBOT SKETCH DETAILS--"
  foreach robotsketch_array
  [
    ask robotsketches with [ID = ?]
    [
      file-print "--NEXT ROBOT SKETCH--"
      file-print ID
      file-print fdbkdrive_speed
      file-print sidedrive_speed
      file-print intake_sides
      file-print primary_launcher_sides
      file-print primary_launcher_speed
      file-print secondary_launcher_sides
      file-print secondary_launcher_speed
      file-print lift_type 
    ]
  ]
  file-print "--ROBOT DETAILS--"
  foreach robot_array
  [
    ask robots with [robotID = ?]
    [
      file-print "--NEXT ROBOT--"
      file-print robotID
      file-print robotSketchID
      file-print startingTile
    ]
  ]
  file-print "--FRAME DETAILS--"
  foreach frames_array
  [
    ask frames with [frameID = ?]
    [
      file-print "--NEXT FRAME--"
      file-print frameID
      file-print currentrobot_array
      file-print robotXs
      file-print robotYs
      file-print robotHs
      file-print robotCaps
      file-write robotEls
      file-print ""
      file-write pyramids
      file-print ""
      file-print bScore
      file-print rScore
      file-print bLoads
      file-print rLoads
    ]
  ]
  file-print "--END FILE--"
  file-close
end

to importFilm
  hardreset
  file-close-all
  file-open user-file
  let file-info []
  while [not file-at-end?]
  [
    set file-info lput file-read-line file-info
  ]
  let current-index 0
  carefully
  [
    if not (item current-index file-info = "--BEGIN FILE--")
    [
      print item current-index file-info
      error "File header was unreadable!"
    ]
    set current-index current-index + 1
    if not (item current-index file-info = "--ROBOT SKETCH DETAILS--")
    [
      error "Robot sketches header was unreadable!"
    ]
    set current-index current-index + 1
    while [item current-index file-info = "--NEXT ROBOT SKETCH--"]
    [
      create-robotsketches 1 [
        set size 0
        set ID item (current-index + 1) file-info
        set fdbkdrive_speed read-from-string(item (current-index + 2) file-info)
        set sidedrive_speed read-from-string(item (current-index + 3) file-info)
        set intake_sides item (current-index + 4) file-info
        set primary_launcher_sides item (current-index + 5) file-info
        set primary_launcher_speed read-from-string(item (current-index + 6) file-info)
        set secondary_launcher_sides item (current-index + 7) file-info
        set secondary_launcher_speed read-from-string(item (current-index + 8) file-info)
        set lift_type item (current-index + 9) file-info
        set robotsketch_array lput ID robotsketch_array
      ]
      set current-index current-index + 10
    ]
    if not (item current-index file-info = "--ROBOT DETAILS--")
    [
      error "Robots header was unreadable!"
    ]
    set current-index current-index + 1
    while [item current-index file-info = "--NEXT ROBOT--"]
    [
      create-robots 1 [
        set shape "square"
        set heading 0
        set size 10
        set robotID item (current-index + 1) file-info
        set robot_array lput robotID robot_array
        set robotsketchID item (current-index + 2) file-info
        set startingTile item (current-index + 3) file-info
        set elevation "None"
        set capacity []
        ifelse(startingTile = "Far Blue")
        [
          setxy 0 1
          set alliance "Blue"
        ]
        [
          ifelse(startingTile = "Close Blue")
          [
            setxy 1 0
            set alliance "Blue"
          ]
          [
            ifelse(startingTile = "Far Red")
            [
              setxy 5 1
              set alliance "Red"
            ]
            [
              setxy 4 0
              set alliance "Red"
            ]
          ]
        ]
        set color (position robotID robot_array + 1) * 20 + 5
      ]
      create-rollers 1 [
        set rollerID last robot_array
        set shape (word "roller" first([intake_sides] of robotsketches with [ID = first ([robotSketchID] of robots with [robotID = last robot_array])]))
        set heading 0
        set size 10
        setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
      ]
      create-baseDrives 1 [
        set baseID last robot_array
        ifelse (first([fdbkdrive_speed] of robotsketches with [ID = first([robotSketchID] of robots with [robotID = last robot_array])]) = 0)
        [
          set shape "driveblank"
        ]
        [
          ifelse (first([sidedrive_speed] of robotsketches with [ID = first([robotSketchID] of robots with [robotID = last robot_array])]) = 0)
          [
            set shape "drivetank"
          ]
          [
            set shape "drivex"
          ]
        ]
        set heading 0
        set size 10
        setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
      ]
      create-primary-launchers 1 [
        set plaunchID last robot_array
        set shape (word "plaunch" first([primary_launcher_sides] of robotsketches with [ID = first ([robotSketchID] of robots with [robotID = last robot_array])]))
        set heading 0
        set size 10
        setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
      ]
      create-secondary-launchers 1 [
        set slaunchID last robot_array
        set shape (word "slaunch" first([secondary_launcher_sides] of robotsketches with [ID = first ([robotSketchID] of robots with [robotID = last robot_array])]))
        set heading 0
        set size 10
        setxy first([xcor] of robots with [robotID = last robot_array]) first([ycor] of robots with[robotID = last robot_array])
      ]
      set current-index current-index + 4
    ]
    if not (item current-index file-info = "--FRAME DETAILS--")
    [
      error "Frames header was unreadable!"
    ]
    set current-index current-index + 1
    while [item current-index file-info = "--NEXT FRAME--"]
    [
      create-frames 1 [
        set size 0
        set frameID item (current-index + 1) file-info
        set frames_array lput frameID frames_array
        set currentrobot_array robot_array
        set robotXs read-from-string(item (current-index + 3) file-info)
        set robotYs read-from-string(item (current-index + 4) file-info)
        set robotHs read-from-string(item (current-index + 5) file-info)
        set robotCAPs read-from-string(item (current-index + 6) file-info)
        set robotELs read-from-string(item (current-index + 7) file-info)
        set pyramids read-from-string(item (current-index + 8) file-info)
        set bscore read-from-string(item (current-index + 9) file-info)
        set rscore read-from-string(item (current-index + 10) file-info)
        set bloads read-from-string(item (current-index + 11) file-info)
        set rloads read-from-string(item (current-index + 12) file-info)
      ]
      set current-index current-index + 13
    ]
    if not (item current-index file-info = "--END FILE--")
    [
      error "File footer was unreadable!"
    ]
  ]
  [
    user-message "Exception! This file may be corrupt! Double-check that this is the correct file, and try again!"
    user-message error-message
  ]
  file-close-all
end

to generateCode
  file-close-all
  file-open user-new-file
  let fileName user-input "Enter a name for this routine:"
  file-print "//Automatically generated code via VRC 5327B NbN Simulation"
  file-print (word "void " fileName "()")
  file-print "{"
  let currentFrameCode 1
  let initialX 0
  let initialY 0
  let initialH 0
  let endX 0
  let endY 0
  let endH 0
  let desiredRobotIndex 0
  ask robots with [startingtile = robotbeingdriven]
  [
    set desiredRobotIndex position robotID robot_array
  ]
  ask frames with [frameID = item 0 frames_array]
    [
      set endX item desiredRobotIndex robotXs
      set endY item desiredRobotIndex robotYs
      set endH item desiredRobotIndex robotHs
    ]
  while [currentFrameCode < length frames_array]
  [
    set initialX endX
    set initialY endY
    set initialH endH
    ask frames with [frameID = item currentFrameCode frames_array]
    [
      file-print word "  //" frameID
      set endX item desiredRobotIndex robotXs
      set endY item desiredRobotIndex robotYs
      set endH item desiredRobotIndex robotHs
    ]
    if endH != initialH
    [
      let turn abs(TURN_SCALE * (initialH - endH))
      ifelse initialH < endH
      [
        file-print (word "  ABase(0, 0, 127, " round(turn) ");")
      ]
      [
        file-print (word "  ABase(0, 0, -127, " round(turn) ");")
      ]
    ]
    if endX != initialX or endY != initialY
    [
      let distanceToTravel sqrt((endX - initialX) ^ 2 + (endY - initialY) ^ 2)
      let straight distanceToTravel * DRIVE_SCALE
      let xcomp endX - initialX
      let ycomp endY - initialY
      let angle (atan xcomp ycomp) - initialH
      let xpower round(127 * cos(angle))
      let ypower round(127 * sin(angle)) 
      file-print (word "  ABase(" xpower ", " ypower ", 0, " round(straight) ");")
    ]
    set currentFrameCode currentFrameCode + 1
  ]
  file-print "}"
  file-close-all
end
@#$#@#$#@
GRAPHICS-WINDOW
538
10
1058
551
-1
-1
17.0
1
10
1
1
1
0
0
0
1
0
29
0
29
0
0
1
ticks
10.0

BUTTON
301
290
377
335
Reset Field
reset-field
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
377
290
451
335
Start Match
if(running? = false)\n[\nset running? True\n]\ngo
T
1
T
OBSERVER
NIL
NIL
NIL
NIL
0

BUTTON
226
173
289
206
Up
up
NIL
1
T
OBSERVER
NIL
W
NIL
NIL
0

BUTTON
289
206
352
239
Right
strafeR
NIL
1
T
OBSERVER
NIL
D
NIL
NIL
0

BUTTON
163
206
226
239
Left
strafeL
NIL
1
T
OBSERVER
NIL
A
NIL
NIL
0

BUTTON
226
206
289
239
Down
down
NIL
1
T
OBSERVER
NIL
S
NIL
NIL
0

BUTTON
289
173
352
206
RTurn
rturn
NIL
1
T
OBSERVER
NIL
E
NIL
NIL
0

BUTTON
163
173
226
206
LTurn
lturn
NIL
1
T
OBSERVER
NIL
Q
NIL
NIL
0

BUTTON
163
239
352
273
Shoot
shoot
NIL
1
T
OBSERVER
NIL
J
NIL
NIL
1

MONITOR
399
109
452
154
Time:
time
1
1
11

BUTTON
352
206
451
240
Load Driver Load
load
NIL
1
T
OBSERVER
NIL
L
NIL
NIL
1

BUTTON
352
173
451
207
Elevate
elevate
NIL
1
T
OBSERVER
NIL
K
NIL
NIL
1

BUTTON
1061
114
1207
147
Create Robot Sketch
robotsketchCreate
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1221
81
1311
114
Add Robot
addRobotToField
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1061
81
1207
114
Import Robot Sketch
importrobotsketch
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1061
147
1207
180
Export Robot Sketch
exportrobotsketch
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1324
82
1427
115
HARD RESET
hardreset
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
352
240
451
273
Thumbs Up!
set cstep 0
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

OUTPUT
538
551
1058
605
12

CHOOSER
163
290
301
335
RobotBeingDriven
RobotBeingDriven
"Far Blue" "Close Blue" "Far Red" "Close Red"
0

MONITOR
163
109
345
154
Capacity
first([capacity] of robots with [startingTile = robotbeingdriven])
17
1
11

MONITOR
345
109
399
154
Elevation
first([elevation] of robots with [startingTile = robotbeingdriven])
17
1
11

MONITOR
277
64
452
109
Blue Alliance Loads Remaining
blueloads
17
1
11

MONITOR
277
19
452
64
Red Alliance Loads Remaining
redloads
17
1
11

MONITOR
1062
227
1313
272
Robot Sketches
robotsketch_array
17
1
11

MONITOR
1062
272
1313
317
Robots
robot_array
17
1
11

BUTTON
1061
180
1207
213
Delete Robot Sketch
deletesketch
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1221
114
1311
147
Delete Robot
robotDelete\n
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

MONITOR
163
19
277
64
Red Alliance Score
RedScore
17
1
11

MONITOR
163
64
277
109
Blue Alliance Score
bluescore
17
1
11

BUTTON
1181
330
1289
363
Reset Frames
reset-frames
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1062
330
1181
363
Add New Frame
add-frame
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

MONITOR
1063
404
1289
449
Frames
frames_array
17
1
11

BUTTON
1062
363
1181
396
Display Frame
showframe
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1181
363
1289
396
Delete Frame
deleteFrame
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1183
477
1286
510
Next Frame
nextframe
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1066
477
1183
510
Previous Frame
previousFrame
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

MONITOR
1295
404
1389
449
Current Frame
currFrame
17
1
11

SWITCH
163
338
268
371
Practice?
Practice?
0
1
-1000

BUTTON
1066
519
1183
554
Export Match Film
exportFilm
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1183
519
1287
554
Import Match Film
importFilm
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
1067
565
1288
598
Generate RobotC Code
generateCode
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

@#$#@#$#@
## WHAT IS IT?

(a general understanding of what the model is trying to show or explain)

## HOW IT WORKS

(what rules the agents use to create the overall behavior of the model)

## HOW TO USE IT

(how to use the model, including a description of each of the items in the Interface tab)

## THINGS TO NOTICE

(suggested things for the user to notice while running the model)

## THINGS TO TRY

(suggested things for the user to try to do (move sliders, switches, etc.) with the model)

## EXTENDING THE MODEL

(suggested things to add or change in the Code tab to make the model more complicated, detailed, accurate, etc.)

## NETLOGO FEATURES

(interesting or unusual features of NetLogo that the model uses, particularly in the Code tab; or where workarounds were needed for missing features)

## RELATED MODELS

(models in the NetLogo Models Library and elsewhere which are of related interest)

## CREDITS AND REFERENCES

(a reference to the model's URL on the web if it has one, as well as any other necessary credits, citations, and links)
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

back
true
0
Rectangle -2674135 true false 120 180 180 195

both
true
0
Rectangle -2674135 true false 120 195 180 210
Rectangle -2674135 true false 120 90 180 105

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 0 0 300

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

driveblank
true
0

drivetank
true
0
Rectangle -14835848 true false 90 90 105 120
Rectangle -14835848 true false 90 180 105 210
Rectangle -14835848 true false 195 90 210 120
Rectangle -14835848 true false 195 180 210 210
Rectangle -16777216 false false 90 90 105 120
Rectangle -16777216 false false 195 90 210 120
Rectangle -16777216 false false 195 180 210 210
Rectangle -16777216 false false 90 180 105 210

drivex
true
0
Polygon -14835848 true false 90 120 105 135 135 105 120 90 90 120
Polygon -14835848 true false 210 120 195 135 165 105 180 90 210 120
Polygon -14835848 true false 90 180 105 165 135 195 120 210 90 180
Polygon -14835848 true false 210 180 195 165 165 195 180 210 210 180
Polygon -16777216 false false 90 180 105 165 135 195 120 210
Polygon -16777216 false false 90 120 105 135 135 105 120 90
Polygon -16777216 false false 210 120 195 135 165 105 180 90
Polygon -16777216 false false 210 180 195 165 165 195 180 210

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

front
true
0
Rectangle -2674135 true false 120 105 180 120

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

launcher
true
0
Circle -2674135 true false 103 103 92
Rectangle -1184463 true false 135 60 165 165

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

nbnball
true
2
Circle -955883 true true 135 135 30
Circle -16777216 false false 135 135 30

nbnpyramid
true
0
Circle -13840069 true false 135 150 30
Circle -13840069 true false 120 120 30
Circle -13840069 true false 150 120 30
Circle -16777216 false false 150 120 30
Circle -16777216 false false 120 120 30
Circle -16777216 false false 135 150 30
Circle -955883 true false 135 135 30
Circle -16777216 false false 135 135 30

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

plaunchback
true
0
Rectangle -8630108 true false 165 135 195 195
Polygon -13345367 true false 165 150 180 165 195 150 180 135 165 150
Rectangle -16777216 false false 165 135 195 195

plaunchfront
true
0
Rectangle -8630108 true false 165 105 195 165
Polygon -13345367 true false 165 150 180 135 195 150 180 165 165 150
Rectangle -16777216 false false 165 105 195 165

plaunchnone
true
0

robot
true
0
Polygon -16777216 true false 75 105 105 75 120 90 90 120
Polygon -16777216 true false 75 105 105 75 120 90 90 120
Polygon -16777216 true false 195 75 225 105 210 120 180 90
Polygon -16777216 true false 180 210 210 180 225 195 195 225
Polygon -16777216 true false 105 225 75 195 90 180 120 210
Polygon -7500403 true true 90 120 90 180 120 210 135 180 135 165 165 165 165 180 180 210 210 180 210 120 180 90 165 120 165 135 135 135 135 120 120 90
Rectangle -2674135 true false 135 90 165 105

rollerback
true
0
Polygon -10899396 true false 105 210 105 195 195 195 195 210 105 210
Rectangle -16777216 false false 105 195 195 210

rollerboth
true
0
Polygon -10899396 true false 105 210 105 195 195 195 195 210 105 210
Polygon -10899396 true false 105 105 105 90 195 90 195 105 105 105
Rectangle -16777216 false false 105 195 195 210
Rectangle -16777216 false false 105 90 195 105

rollerfront
true
0
Polygon -10899396 true false 105 90 105 105 195 105 195 90 105 90
Rectangle -16777216 false false 105 90 195 105

rollers
true
0
Rectangle -13840069 true false 105 135 135 165
Rectangle -13840069 true false 165 135 195 165
Circle -13840069 true false 165 150 30
Circle -13840069 true false 165 120 30
Circle -13840069 true false 105 150 30
Circle -13840069 true false 105 120 30

sheep
false
15
Circle -1 true true 203 65 88
Circle -1 true true 70 65 162
Circle -1 true true 150 105 120
Polygon -7500403 true false 218 120 240 165 255 165 278 120
Circle -7500403 true false 214 72 67
Rectangle -1 true true 164 223 179 298
Polygon -1 true true 45 285 30 285 30 240 15 195 45 210
Circle -1 true true 3 83 150
Rectangle -1 true true 65 221 80 296
Polygon -1 true true 195 285 210 285 210 240 240 210 195 210
Polygon -7500403 true false 276 85 285 105 302 99 294 83
Polygon -7500403 true false 219 85 210 105 193 99 201 83

slaunchback
true
0
Rectangle -5825686 true false 105 135 135 195
Polygon -13345367 true false 135 150 120 165 105 150 120 135 135 150
Rectangle -16777216 false false 105 135 135 195

slaunchfront
true
0
Rectangle -5825686 true false 105 105 135 165
Polygon -13345367 true false 135 150 120 135 105 150 120 165 135 150
Rectangle -16777216 false false 105 105 135 165

slaunchnone
true
0

square
true
0
Rectangle -7500403 true true 105 105 195 195
Rectangle -16777216 false false 105 105 195 195

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tile
false
0
Rectangle -7500403 true true 135 135 165 165

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

tri
true
0
Polygon -7500403 true true 135 165 135 135 165 165

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

wolf
false
0
Polygon -16777216 true false 253 133 245 131 245 133
Polygon -7500403 true true 2 194 13 197 30 191 38 193 38 205 20 226 20 257 27 265 38 266 40 260 31 253 31 230 60 206 68 198 75 209 66 228 65 243 82 261 84 268 100 267 103 261 77 239 79 231 100 207 98 196 119 201 143 202 160 195 166 210 172 213 173 238 167 251 160 248 154 265 169 264 178 247 186 240 198 260 200 271 217 271 219 262 207 258 195 230 192 198 210 184 227 164 242 144 259 145 284 151 277 141 293 140 299 134 297 127 273 119 270 105
Polygon -7500403 true true -1 195 14 180 36 166 40 153 53 140 82 131 134 133 159 126 188 115 227 108 236 102 238 98 268 86 269 92 281 87 269 103 269 113

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270

@#$#@#$#@
NetLogo 5.1.0
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180

@#$#@#$#@
0
@#$#@#$#@
