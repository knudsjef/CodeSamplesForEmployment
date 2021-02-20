using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/**
 * This is an abstract class for a game my friends and I were developing. There were different shapes that all had different abilities
 * and this was the base class for the all of the shapes.
 */ 
namespace Assets.Scripts.Shapes
{
    public abstract class Shape
    {
        public static Animator playerAnimator;
        public static float OnGroundDistance = 0.2f;
        public int Speed;
        public int JumpHeight;
        public Collider2D ShapeCollider;
        public Sprite ShapeSprite;
        public float MoveAdditive = 0;
        public Rigidbody2D playerRigid;

        /// <summary>
        /// Initializes the shape character
        /// </summary>
        public abstract void InitializeShape();

        /// <summary>
        /// Enables the collider
        /// </summary>
        public void Enable()
        {
            ShapeCollider.enabled = true;
        }

        /// <summary>
        /// Disables the collider
        /// </summary>
        public void Disable()
        {
            ShapeCollider.enabled = false;
        }

        /// <summary>
        /// Causes the player to jump
        /// </summary>
        public virtual void Jump()
        {
            playerRigid.velocity = new Vector2(playerRigid.velocity.x, JumpHeight);
        }

        /// <summary>
        /// Activiates the shapes specific special ability
        /// </summary>
        /// <param name="player">The gameobject of the player</param>
        public abstract void ActivateSpecial(GameObject player);

        /// <summary>
        /// Moves the player based on input
        /// </summary>
        /// <param name="directionMultiplier">The normalized direction</param>
        public virtual void Move(float directionMultiplier)
        {
            playerRigid.velocity = new Vector2((Speed * directionMultiplier) + MoveAdditive, playerRigid.velocity.y);
        }

    }
}
