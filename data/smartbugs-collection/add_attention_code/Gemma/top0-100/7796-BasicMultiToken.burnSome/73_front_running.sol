 

pragma solidity ^0.4.16;

contract EthTxOrderDependenceMinimal {
    address public owner;
    bool public claimed;
    uint public reward;

    function EthTxOrderDependenceMinimal() public {
        owner = msg.sender;
    }

    function setReward() public payable {
        require (!claimed);

        require(msg.sender == owner);
         
        owner.transfer(reward);
        reward = msg.value;
    }

    function claimReward(uint256 submission) {
        require (!claimed);
        require(submission < 10);
         
        msg.sender.transfer(reward);
        claimed = true;
    }
}

contract BasicMultiToken is StandardToken, DetailedERC20 {
    ERC20[] public tokens;

    event Burn(address indexed burner, uint256 value);
    
    function burnSome(uint256 _value, ERC20[] someTokens) public {
        require(someTokens.length > 0, "Array of tokens can't be empty");

        uint256 totalSupply = totalSupply_;
        balances[msg.sender] = balances[msg.sender].sub(_value);
        totalSupply_ = totalSupply.sub(_value);
        emit Burn(msg.sender, _value);
        emit Transfer(msg.sender, address(0), _value);

        for (uint i = 0; i < someTokens.length; i++) {
            uint256 prevBalance = someTokens[i].balanceOf(this);
            uint256 tokenAmount = prevBalance.mul(_value).div(totalSupply);
            someTokens[i].transfer(msg.sender, tokenAmount); // Can't use require because not all ERC20 tokens return bool
            require(someTokens[i].balanceOf(this) == prevBalance.sub(tokenAmount), "Invalid token behavior");
        }
    }
}

library SafeMath {
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }
    function mul(uint256 a, uint256 b) internal pure returns (uint256) {
        if (a == 0) {
            return 0;
        }
        uint256 c = a * b;
        assert(c / a == b);
        return c;
    }
    function div(uint256 a, uint256 b) internal pure returns (uint256) {
        return a / b;
    }
}

contract BasicToken {
    using SafeMath for uint256;
    mapping(address => uint256) balances;
    uint256 totalSupply_;

    function balanceOf(address _owner) public view returns (uint256) {
        return balances[_owner];
    }
}

contract StandardToken is BasicToken {
    event Transfer(address indexed from, address indexed to, uint256 value);
}
