/*---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 274, Fall  2018
#
#    Final Project
# ---------------------------------------------------*/

int * receivePath( void ) {
    static int pathlen;
    int pathin;
    while (Serial3.available() == 0) { }// block until read in length
    // Read in path length
    pathlen = Serial3.read();
    Serial.print("length received: ");
    Serial.println(pathlen);

    // Read in path

    static int * path;
    path = (int*)malloc(pathlen+1 * sizeof(int));
    path[0] = pathlen;
    for (int i = 1; i <= pathlen; i++) {
        while (Serial3.available() == 0){ } // wait until available
        Serial.print(i);
        Serial.print(" path received: ");
        pathin = Serial3.read();
        Serial.print(char(pathin));
        path[i] = pathin;
        Serial.println(path[i]);
    }
    delay(500);
    /*
    for (int i = 0; i < pathlen; i++) {
        Serial.println(path[i]);
        Serial.flush();
    }
    */

    return path;
}
