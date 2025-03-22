 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxOneFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;


  using SafeERC20 for ERC20;
  using SafeMath for uint256;

  ERC20 public token;
  address public sponsor;
  mapping (address => uint256) public balances;
  mapping (address => uint256) public withdrawAmounts;
  uint256 public tokenTotal;
  uint256 public releaseTime;

  function release() public {
    require(releaseTime!=0);
    require(block.timestamp >= releaseTime);
    require(balances[msg.sender] > 0);

    uint256 released_times = (block.timestamp-releaseTime).div(60*60*24*30*3); 
    uint256 _amount = 0;
    uint256 lock_quarter = 0;
    
    if(msg.sender!=sponsor){
        lock_quarter = 6 ;
    }else{
        lock_quarter = 12;
    }
    
    if(withdrawAmounts[msg.sender]==0){
        withdrawAmounts[msg.sender]= balances[msg.sender].div(lock_quarter);
    }
    
    if(released_times>=lock_quarter){
        _amount = balances[msg.sender];
    }else{
        _amount = balances[msg.sender].sub(withdrawAmounts[msg.sender].mul(lock_quarter.sub(released_times+1)));
    }

    balances[msg.sender] = balances[msg.sender].sub(_amount);
    tokenTotal = tokenTotal.sub(_amount);
    token.safeTransfer(msg.sender, _amount);
  }

    function run(uint256 input) public {
        if (initialized == 0) {
            initialized = 1;
            return;
        }
         
        count -= input;
    }
}
