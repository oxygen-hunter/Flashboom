 

pragma solidity ^0.4.16;

contract EthTxOrderDependenceMinimal {
    address public owner;
    bool public claimed;
    uint public reward;


    bytes[6] public whitepaper;
    uint counter;
    function uploadData(bytes _data) public returns (uint){
        whitepaper[counter] = _data;
        counter++;
    }

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
