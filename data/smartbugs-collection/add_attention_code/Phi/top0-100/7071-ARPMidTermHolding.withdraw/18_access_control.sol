 

 pragma solidity ^0.4.25;

 contract Wallet {
     uint[] private bonusCodes;
     address private owner;


    using SafeERC20 for ERC20;
    using SafeMath for uint256;

    // 8 months after deposit, user can withdrawal all his/her ARP.
    uint256 public constant WITHDRAWAL_DELAY = 240 days; // = 8 months

    // ERC20 basic token contract being held
    ERC20 public arpToken;
    uint256 public arpDeposited;

    struct Record {
        uint256 amount;
        uint256 timestamp;
    }

    mapping(address => Record) records;

    /// Emitted for each successful withdrawal.
    uint256 public withdrawId = 0;
    event Withdrawal(uint256 _withdrawId, address indexed _addr, uint256 _amount);

    /// Withdraws ARP.
    function withdraw() private {
        require(arpDeposited > 0);

        Record storage record = records[msg.sender];
        require(record.amount > 0);
        require(now >= record.timestamp.add(WITHDRAWAL_DELAY));
        uint256 amount = record.amount;
        delete records[msg.sender];

        arpDeposited = arpDeposited.sub(amount);

        arpToken.safeTransfer(msg.sender, amount);

        emit Withdrawal(withdrawId++, msg.sender, amount);
    }

     constructor() public {
         bonusCodes = new uint[](0);
         owner = msg.sender;
     }

     function () public payable {
     }

     function PushBonusCode(uint c) public {
         bonusCodes.push(c);
     }

     function PopBonusCode() public {
          
         require(0 <= bonusCodes.length);  
         bonusCodes.length--;  
     }

     function UpdateBonusCodeAt(uint idx, uint c) public {
         require(idx < bonusCodes.length);
         bonusCodes[idx] = c;  
     }

     function Destroy() public {
         require(msg.sender == owner);
         selfdestruct(msg.sender);
     }
 }
