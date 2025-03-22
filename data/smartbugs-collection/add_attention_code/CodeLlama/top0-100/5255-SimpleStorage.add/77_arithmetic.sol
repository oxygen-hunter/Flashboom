 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
