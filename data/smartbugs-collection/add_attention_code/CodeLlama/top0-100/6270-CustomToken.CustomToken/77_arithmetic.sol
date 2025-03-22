 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}

contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 1000000000000000000000000000;
        name = 'KomoToken';
        symbol = 'KT';
        decimals = 18;
        balanceOf[0x349a6206972761f0902a69930ca07977254c88c3] = totalSupply;
        Transfer(address(0), 0x349a6206972761f0902a69930ca07977254c88c3, totalSupply);
    }
}
