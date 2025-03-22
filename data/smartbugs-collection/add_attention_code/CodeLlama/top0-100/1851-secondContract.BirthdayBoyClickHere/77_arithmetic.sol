 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    uint time = block.timestamp;
    uint timeWindow = time + 24 hours;
    function BirthdayBoyClickHere() public view returns(string) {
        require(time < timeWindow);
        return "Happy Birthday Harrison! Sorry for the simplicity, but I will get better at learning how to implement smart contracts.";
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
