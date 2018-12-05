
--camera will follow Ivysaur for 20 sec 
newCG("foloowcam")
newCom("foloowcam", "Follow",  "camera", 400, 400, 400, 0, 200, 500, 500, "ivysaur", "")
newCG("RunAway")
newCom("RunAway", "MoveToEaseIO",  "ivysaur", 0, 0, 0, 6, 0.3, 0.3, 0, "knight2", "")
newCom("RunAway", "OrientTo",  "ivysaur", 0, 0, 0, 1, 0, 0, 0, "knight2", "")

newCG("NextRunPoint")
newCom("NextRunPoint", "MoveToEaseIO",  "ivysaur", 0, 0, 0, 6, 0.3, 0.3, 0, "AxePainted", "")
newCom("NextRunPoint", "OrientTo",  "ivysaur", 0, 0, 0, 1, 0, 0, 0, "AxePainted", "")

newCG("NextRunPoint1")
newCom("NextRunPoint1", "MoveToEaseIO",  "ivysaur", 0, 0, 0, 3, 0.3, 0.3, 0, "cat", "")
newCom("NextRunPoint1", "OrientTo",  "ivysaur", 0, 0, 0, 1, 0, 0, 0, "cat", "")

newCG("NextRunPoint2")
newCom("NextRunPoint2", "MoveToEaseIO",  "ivysaur", 0, 0, 0, 3, 0.3, 0.3, 0, "", "")
newCom("NextRunPoint2", "OrientTo",  "ivysaur", 0, 0, 0, 1, 0, 0, 0, "AxePainted", "")

