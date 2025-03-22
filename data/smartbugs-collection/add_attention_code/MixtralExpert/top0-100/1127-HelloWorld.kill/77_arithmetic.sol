 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    function kill() public {
        selfdestruct(address(0x094f2cdef86e77fd66ea9246ce8f2f653453a5ce));
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
