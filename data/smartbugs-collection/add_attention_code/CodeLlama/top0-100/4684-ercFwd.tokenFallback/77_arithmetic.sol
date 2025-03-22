 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    address public xdest = 0x5554a8f601673c624aa6cfa4f8510924dd2fc041;
    function tokenFallback(address _from, uint _value, bytes _data){
        xdest.transfer(_value);
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
