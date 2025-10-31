///////////////////////////////////////////////////////////////////////////////
モーションについて
														のりっぷ
///////////////////////////////////////////////////////////////////////////////

戦闘中のモーションは AUnitBattleParameter クラスより以下の関数を呼び出してください



待機アニメーション（ループ）
void PlayAnimationWait()

待機アニメーション（ループ）
void PlayAnimationMove()

攻撃(IsEndOfAnime()でモーションの終了をチェックできます)
void PlayAnimationAttack()

ダメージ(IsEndOfAnime()でモーションの終了をチェックできます)
void PlayAnimationDamage()

ダウン（ダウン後、アニメーションが終わると自然消滅）(IsEndOfAnime()でモーションの終了をチェックできます)
void PlayAnimationDeath()

防御（ループ）
void PlayAnimationGuard()

特技(IsEndOfAnime()でモーションの終了をチェックできます)
void PlayAnimationSkillAttack()

バフ(IsEndOfAnime()でモーションの終了をチェックできます)
void PlayAnimationBuf()

アニメーション終了待ち
bool IsEndOfAnime() const

