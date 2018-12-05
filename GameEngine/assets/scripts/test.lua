--Create New Command Group
newCG("Main")
newSubCG("Main", "PickUp_pockeball")
--Create New commands and add it to existing command group to run them parallel
-- (Group Name, CommandName, objName, x, y, z, time, EaseIn from 0 to 1, EaseOut, Target Obj, ScriptName)
newCom("PickUp_pockeball", "MoveToEaseIO",  "knight", 0, 0, 0, 8, 0.3, 0.3, 0, "pokeball", "")
newCom("PickUp_pockeball", "OrientTo",  "knight", 0, 0, 0, 7, 0, 0, 0, "pokeball", "")
--Command group that will run After previous CG is finished
newSubCG("Main", "PrepareToThrow")
newCom("PrepareToThrow", "MoveToEaseIO",  "knight", 0, 0, 0, 4, 0.4, 0.4, 0, "teapot", "")
--example of "follow" command
--where  (..., ..., ... IdealRelPos, FollowTime(0 = forever), MinDist, MaxSpeedDis, MaxSpeed, target)
newCom("PrepareToThrow", "Follow",  "pokeball", 100, 100, 100, 6, 50, 200, 400, "knight", "")
--Aiming to throw pokeball
newSubCG("Main", "Aim")
newCom("Aim", "OrientTo",  "knight", 0, 0, 0, 3, 0, 0, 0, "ivysaur", "")
--Throw!
newSubCG("Main", "ballisticTrow")
--example of follow Bezier curve command
--where  (..., ..., obj to move, x,y,z -control point, time, x,y,z destination OR destination object)
newCom("ballisticTrow", "FollowCurve", "pokeball", 0, 1000, 0, 4, 0, 0, 0, "ivysaur", "")

--pokeball trigged ivysaur
--newCG("IvyTrigger")
--example of trigger command
--where (..., ..., obj that we checking, x,y,z -trigger point (if no target object), radius, object-location trigger, script that will run)
newCom("Main", "Trigger",  "pokeball", 0, 0, 0, 50, 0, 0, 0, "ivysaur", "trig.lua")




--newCom("Gr2", "MoveToEaseIO",  "knight2", 0, 0, 0, 10, 0, 0, 0, "cat", "")

---newCG("g1")
--newCom("g1", "MoveToEaseIO", "camera", 0, 0, 0, 10, 0.3, 0.3, 0, "cat", "")

--newCG("Gr2")
--newCom("Gr2", "OrientTo",  "camera", 0, 0, 0, 5, 0, 0, 0, "cat", "")

--newCG("Gr2")
--newCom("Gr2", "Follow",  "camera", 400, 400, 400, 10, 100, 500, 500, "cat", "")

--newCG("g2")
--newCom("g2", "FollowCurve", "knight2", 0, 0, 0, 10, 0, 0, 0, "cat", "")

--newCG("g3")
--newCom("g1", "MoveToEaseIO", "knight2", 0, 0, 0, 10, 0.3, 0.3, 0, "cat", "")
--newCom("g3", "Trigger", "knight2", 0, 0, 0, 100, 0, 0, 0, "cat", "trig.lua")

--newCG("Gr2")
-- (Group Name, CommandName, objName, x, y, z, time, EaseIn from 0 to 1, EaseOut, Target Obj, ScriptName)
--(IdealRelPos, FollowTime(0 = forever), MinDist, MaxSpeedDis, MaxSpeed, target)
--newCom("Gr2", "Follow",  "knight2", 400, 400, 400, 10, 100, 500, 500, "cat", "")
--newCom("Gr2", "OrientTo",  "knight2", 0, 0, 0, 10, 0, 0, 0, "cat", "")