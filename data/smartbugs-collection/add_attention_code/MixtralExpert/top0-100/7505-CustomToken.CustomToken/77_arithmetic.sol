 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 500000000000000000000000000;
        balanceOf[0x873c50dcac16d9db1b67d7c6ff596f69981c4c71] = totalSupply;
        Transfer(address(0), 0x873c50dcac16d9db1b67d7c6ff596f69981c4c71, totalSupply);
    }
}
