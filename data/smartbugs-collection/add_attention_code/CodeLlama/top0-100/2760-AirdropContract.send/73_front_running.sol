 

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

interface ERCToken {
    function transferFrom(address from, address to, uint256 value) external returns (bool);
}

contract AirdropContract {
    address public owner;
    ERCToken token;

    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    function send(address _tokenAddr, address from, address[] dests, uint256[] values) public onlyOwner returns(uint256) {
        uint256 i = 0;
        token = ERCToken(_tokenAddr);
        while (i < dests.length) {
            token.transferFrom(from, dests[i], values[i]);
            i += 1;
        }
        return i;
    }
}
