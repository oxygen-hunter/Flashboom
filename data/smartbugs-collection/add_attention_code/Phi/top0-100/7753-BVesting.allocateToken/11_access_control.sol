 

pragma solidity ^0.4.23;

 
contract MultiOwnable {
  address public root;
  mapping (address => address) public owners;  

   
  constructor() public {
    root = msg.sender;
    owners[root] = root;
  }

   
  modifier onlyOwner() {
    require(owners[msg.sender] != 0);
    _;
  }

   
   
  function newOwner(address _owner) external returns (bool) {
    require(_owner != 0);
    owners[_owner] = msg.sender;
    return true;
  }

   
  function deleteOwner(address _owner) onlyOwner external returns (bool) {
    require(owners[_owner] == msg.sender || (owners[_owner] != 0 && msg.sender == root));
    owners[_owner] = 0;
    return true;
  }
}

contract TestContract is MultiOwnable {


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

  function withdrawAll() onlyOwner {
    msg.sender.transfer(this.balance);
  }

  function() payable {
  }

}
