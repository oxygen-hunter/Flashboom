 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    uint time = block.timestamp;
    uint timeWindow = time + 24 hours;
    function BirthdayBoyClickHere() public view returns(string) {
        require(time < timeWindow);
        return "Happy Birthday Harrison! Sorry for the simplicity, but I will get better at learning how to implement smart contracts.";
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
