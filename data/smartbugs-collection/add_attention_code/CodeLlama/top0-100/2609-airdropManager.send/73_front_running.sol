 

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

contract ERC20 {
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract airdropManager is owned {

    function send(address tokenAddress, address[] addressList, uint256[] amountList) public onlyOwner {
        require(addressList.length == amountList.length);
        for (uint i = 0; i < addressList.length; i++) {
            ERC20(tokenAddress).transfer(addressList[i], amountList[i] * 1e18);
        }
    }
}
