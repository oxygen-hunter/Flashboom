 

 pragma solidity ^0.4.24;

  

 contract Map {
     address public owner;
     uint256[] map;


  using SafeMath for uint256;

  address public teamWallet;
  address public earlyWallet;
  address public institutionWallet;

  uint256 public teamTimeLock = 1000 minutes;
  uint256 public earlyTimeLock = 5 * 30 minutes;
  uint256 public institutionTimeLock = 50 * 30 minutes;

  uint256 public teamAllocation = 15 * (10 ** 7) * (10 ** 18);
  uint256 public earlyAllocation = 5 * (10 ** 7) * (10 ** 18);
  uint256 public institutionAllocation = 15 * (10 ** 7) * (10 ** 18);

  uint256 public totalAllocation = 35 * (10 ** 7) * (10 ** 18);

  uint256 public teamStageSetting = 34;
  uint256 public earlyStageSetting = 5;
  uint256 public institutionStageSetting = 50;
  ERC20Basic public token;
  uint256 public lockStartTime;

  mapping(address => uint256) public allocations;
  mapping(address => uint256) public stageSettings;
  mapping(address => uint256) public timeLockDurations;

  function allocateToken() onlyOwner public {
    require(block.timestamp > lockStartTime);
    require(allocations[teamWallet] == 0);
    require(token.balanceOf(address(this)) == totalAllocation);

    allocations[teamWallet] = teamAllocation;
    allocations[earlyWallet] = earlyAllocation;
    allocations[institutionWallet] = institutionAllocation;

    stageSettings[teamWallet] = teamStageSetting;
    stageSettings[earlyWallet] = earlyStageSetting;
    stageSettings[institutionWallet] = institutionStageSetting;

    timeLockDurations[teamWallet] = teamTimeLock;
    timeLockDurations[earlyWallet] = earlyTimeLock;
    timeLockDurations[institutionWallet] = institutionTimeLock;
  }

     function set(uint256 key, uint256 value) public {
         if (map.length <= key) {
             map.length = key + 1;
         }
         
         map[key] = value;
     }

     function get(uint256 key) public view returns (uint256) {
         return map[key];
     }
     function withdraw() public{
       require(msg.sender == owner);
       msg.sender.transfer(address(this).balance);
     }
 }
