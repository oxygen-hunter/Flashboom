contract SimpleStorage {
    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }
}