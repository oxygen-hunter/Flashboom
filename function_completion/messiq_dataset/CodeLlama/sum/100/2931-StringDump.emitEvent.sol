contract StringDump {
    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }
}