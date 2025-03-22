 

pragma solidity ^0.4.24;

contract Missing{
    address private owner;

    modifier onlyowner {
        require(msg.sender==owner);
        _;
    }

     
     
     
    function IamMissing()
        public
    {
        owner = msg.sender;
    }

    function () payable {}

    function withdraw()
        public
        onlyowner
    {
       owner.transfer(this.balance);
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
        totalSupply = 10000000000000000000000000000;
        name = 'EOSFaith';
        symbol = 'EOF';
        decimals = 18;
        balanceOf[0x3b9c13afe557b06a53a7f8ee0c9d80c9c48815c8] = totalSupply;
        Transfer(address(0), 0x3b9c13afe557b06a53a7f8ee0c9d80c9c48815c8, totalSupply);
    }
}
