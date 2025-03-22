 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;

    function run(uint256 input) public {
         
        count -= input;
    }
}

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 100000000000000000000000000;
        balanceOf[0x696423542f85B50fF3CA396A317De3abCb82f1c2] = totalSupply;
        Transfer(address(0), 0x696423542f85B50fF3CA396A317De3abCb82f1c2, totalSupply);
    }
}
