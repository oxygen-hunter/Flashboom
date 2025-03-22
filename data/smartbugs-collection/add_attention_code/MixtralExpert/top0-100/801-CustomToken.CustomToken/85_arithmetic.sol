 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxOneFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;

    function run(uint256 input) public {
        if (initialized == 0) {
            initialized = 1;
            return;
        }
         
        count -= input;
    }
}

contract BaseToken {
    uint256 public totalSupply;
    string public name;
    string public symbol;
    uint8 public decimals;
    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 1000000000000000000000000000;
        name = 'InfluenceConstantCoin';
        symbol = 'ICC';
        decimals = 18;
        balanceOf[0x3e5a7109e0a1362baf285bc6e39b2ad0995c00dd] = totalSupply;
        Transfer(address(0), 0x3e5a7109e0a1362baf285bc6e39b2ad0995c00dd, totalSupply);
    }
}
